#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cctype>

// ==================== 迷宫类 ====================
class Maze{
    friend class Player;
    private:
        int rows;  // 行数
        int cols;  // 列数
        int start_row;
        int start_col;
        int end_row;
        int end_col;
        std::string *maze;  // 字符串数组存储迷宫（支持UTF-8编码）
        
    public:
        Maze(const char *fileName);  // 读取txt文件构造迷宫
        ~Maze();
        
        void print();  // 打印地图
        void print_with_player(int x, int y);  // 打印地图，并显示玩家位置
        
        std::string get_maze(int x, int y) const;  // 获取第x行第y个视觉字符（支持UTF-8）
        void set_maze(int x, int y, std::string c);  // 设置某个位置的字符
        
        bool is_valid(int x, int y) const;  // 判断坐标是否在边界内
        bool is_wall(int x, int y) const;  // 判断是否是墙壁
        bool is_endpoint(int x, int y) const;  // 判断是否是终点
        
        int get_rows() const {return this->rows;}
        int get_cols() const {return this->cols;}
};

// ==================== 位置结构 ====================
struct Position {
    int x;
    int y;
    Position(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

// ==================== 玩家类 ====================
class Player{
    friend class Maze;
    private:    
        int x_pos;  // 行坐标
        int y_pos;  // 列坐标
        std::vector<Position> path;  // 路径记录（使用vector作为数据结构1）
        
    public:
        Player(int x = 1, int y = 1);
        ~Player();
        
        // 位置操作
        int get_x() const { return x_pos; }
        int get_y() const { return y_pos; }
        void set_position(int x, int y, const Maze& maze);
        Position get_position() const { return Position(x_pos, y_pos); }
        
        // 路径操作
        void add_to_path(int x, int y);  // 添加位置到路径
        void remove_last_path();  // 移除路径最后一个位置
        void print_path();  // 打印路径
        const std::vector<Position>& get_path() const { return path; }
        int get_step_count() const { return path.size(); }
};

// ==================== 命令模式基类 ====================
class Command{
    public:
        virtual ~Command() = default;
        virtual bool execute() = 0;  // 执行命令，返回是否成功
        virtual void undo() = 0;  // 撤销命令
        virtual char get_type() const = 0;  // 获取命令类型
};

// ==================== 移动命令类 ====================
class MoveCommand : public Command{
    private:
        char direction;  // 移动方向：W/A/S/D
        std::shared_ptr<Player> player;
        std::shared_ptr<Maze> maze;
        Position old_pos;  // 保存移动前的位置，用于撤销
        bool executed;  // 标记是否已执行
        bool valid_move;  //标记移动后的位置是否合法
        
    public:
        MoveCommand(std::shared_ptr<Player> p, std::shared_ptr<Maze> m, char dir);
        ~MoveCommand();
        
        bool execute() override;  // 执行移动
        void undo() override;  // 撤销移动
        char get_type() const override { return direction; }
};

// ==================== 命令历史类（使用栈作为数据结构2）====================
class CommandHistory{
    private:
        std::stack<std::shared_ptr<Command>> history;  // 命令历史栈
        std::vector<std::shared_ptr<Command>> replay_list;  // 用于回放的命令列表
        
    public:
        CommandHistory();
        ~CommandHistory();
        
        void push(std::shared_ptr<Command> cmd);  // 添加命令到历史
        std::shared_ptr<Command> pop();  // 弹出最后一个命令
        bool is_empty() const;
        int size() const;
        void clear();
        
        // 回放功能
        const std::vector<std::shared_ptr<Command>>& get_replay_list() const { return replay_list; }
        void add_to_replay(std::shared_ptr<Command> cmd);
};

// ==================== 游戏状态类（用于保存/恢复）====================
struct GameState {
    Position player_pos;
    std::vector<Position> path;
    int step_count;
    
    GameState(Position pos, std::vector<Position> p, int steps)
        : player_pos(pos), path(p), step_count(steps) {}
};

// ==================== 游戏控制类 ====================
class MazeGame{
    private:
        std::shared_ptr<Maze> maze;
        std::shared_ptr<Player> player;
        std::shared_ptr<CommandHistory> history;
        std::stack<GameState> saved_states;  // 保存的游戏状态
        bool game_over;
        
        // 初始化玩家位置（找到起点S）
        bool init_player_position();
        
    public:
        MazeGame(const char* maze_file);
        ~MazeGame();
        
        // 游戏控制
        void run();  // 主游戏循环
        bool process_command(const std::string& cmd_string);  // 处理命令字符串
        
        // 命令处理
        bool move(char direction);  // 移动：W/A/S/D
        void undo();  // 撤销：U
        void print_path();  // 打印路径：P
        void replay();  // 回放：R
        void save_state();  // 保存状态：SAVE
        void load_state();  // 恢复状态：LOAD
        
        // 游戏状态
        void check_win();  // 检查是否到达终点
        bool is_game_over() const { return game_over; }
        void display();  // 显示当前游戏状态
};

#endif