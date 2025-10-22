#include "maze.h"
#include <iostream>
#include <windows.h>
Maze::Maze(const char *filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    
    // 读取行数和列数（可能还有起点和终点坐标）
    std::string first_line;
    std::getline(file, first_line);
    std::istringstream iss(first_line);
    
    iss >> this->rows >> this->cols;
    // 尝试读取起点和终点（如果有的话）
    if(!(iss >> this->start_row >> this->start_col >> this->end_row >> this->end_col)){
        // 如果没有，设为-1，之后自动查找
        this->start_row = this->start_col = -1;
        this->end_row = this->end_col = -1;
    }
    
    this->maze = new std::string[this->rows];
    
    for(int i = 0; i < this->rows; i++){
        std::getline(file, this->maze[i]);
    }
    file.close();
    
    // 自动查找起点和终点（覆盖文件中的坐标，确保准确）
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols; j++){
            std::string ch = get_maze(i, j);
            if(ch == "S"){
                this->start_row = i;
                this->start_col = j;
            }
            else if(ch == "E"){
                this->end_row = i;
                this->end_col = j;
            }
        }
    }
    
    return;
}

Maze::~Maze(){
    delete[] this->maze;
    return;
}

void Maze::print(){
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols; j++){
            std::cout << this->get_maze(i, j) << " ";
        }
        std::cout << std::endl;
    }
}
// 辅助函数：获取UTF-8字符的字节长度
int getUTF8CharLength(unsigned char c){
    if((c & 0x80) == 0) return 1;        // 0xxxxxxx: 单字节
    if((c & 0xE0) == 0xC0) return 2;     // 110xxxxx: 两字节
    if((c & 0xF0) == 0xE0) return 3;     // 1110xxxx: 三字节
    if((c & 0xF8) == 0xF0) return 4;     // 11110xxx: 四字节
    return 1; // 默认返回1
}

std::string Maze::get_maze(int x, int y) const{
    if(x < 0 || x >= this->rows){
        return ""; // 行越界返回空字符串
    }
    
    const std::string& line = this->maze[x];
    
    // 空字符串检查
    if(line.empty()){
        return "";
    }
    
    int charIndex = 0;  // 当前视觉字符索引
    size_t byteIndex = 0;  // 当前字节索引
    
    // 遍历字符串，找到第y个视觉字符
    while(byteIndex < line.length()){
        if(charIndex == y){
            // 找到了第y个字符，提取完整的UTF-8字符
            int charLen = getUTF8CharLength((unsigned char)line[byteIndex]);
            // 确保不会越界
            if(byteIndex + charLen > line.length()){
                return "";
            }
            return line.substr(byteIndex, charLen);
        }
        
        // 跳过当前字符的所有字节
        int charLen = getUTF8CharLength((unsigned char)line[byteIndex]);
        // 确保不会越界
        if(byteIndex + charLen > line.length()){
            break;
        }
        byteIndex += charLen;
        charIndex++;
    }
    
    return ""; // 如果y越界返回空字符串
}

void Maze::print_with_player(int x, int y){
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols; j++){
            if(i == x && j == y){
                std::cout << "P";
            }else{
                std::cout << this->get_maze(i, j);
            }
        }
        std::cout << std::endl;
    }
}

void Maze::set_maze(int x, int y, std::string c){
    // 检查行是否越界
    if(x < 0 || x >= this->rows){
        std::cerr << "错误：行索引越界 (" << x << ")" << std::endl;
        return;
    }
    
    std::string& line = this->maze[x];
    
    // 空字符串检查
    if(line.empty()){
        std::cerr << "错误：该行为空" << std::endl;
        return;
    }
    
    int charIndex = 0;  // 当前视觉字符索引
    size_t byteIndex = 0;  // 当前字节索引
    
    // 遍历字符串，找到第y个视觉字符的位置
    while(byteIndex < line.length()){
        if(charIndex == y){
            // 找到了第y个字符的位置
            // 1. 获取原字符占用的字节数
            int oldCharLen = getUTF8CharLength((unsigned char)line[byteIndex]);
            
            // 边界检查
            if(byteIndex + oldCharLen > line.length()){
                std::cerr << "错误：字符边界越界" << std::endl;
                return;
            }
            
            // 2. 删除原字符（从byteIndex开始删除oldCharLen个字节）
            line.erase(byteIndex, oldCharLen);
            
            // 3. 在同一位置插入新字符c
            line.insert(byteIndex, c);
            
    return;
}

        // 跳过当前字符的所有字节
        int charLen = getUTF8CharLength((unsigned char)line[byteIndex]);
        // 边界检查
        if(byteIndex + charLen > line.length()){
            break;
        }
        byteIndex += charLen;
        charIndex++;
    }
    
    // 如果到这里说明y越界
    std::cerr << "错误：列索引越界 (" << y << "，该行只有 " << charIndex << " 个字符)" << std::endl;
}

bool Maze::is_valid(int x, int y) const{
    if(x >= 0 && x < this->rows && y >= 0 && y < this->cols ){
        return true;
    }
    else{
        return false;
    }
}

bool Maze::is_wall(int x, int y) const{
    if(is_valid(x, y)){
        if(get_maze(x, y) == "#"){
            return true;
        }
    }
    return false;
}

bool Maze::is_endpoint(int x, int y) const{
    if(x == this->end_row && y == this->end_col){
        return true;
    }
    return false;
}

Player::Player(int x, int y) : x_pos(x), y_pos(y){

}

Player::~Player(){
}

void Player::set_position(int x, int y, const Maze& maze){
    if(maze.is_valid(x, y)){
        if(!maze.is_wall(x, y)){
            this->x_pos = x;
            this->y_pos = y;
        }
    }
}

void Player::add_to_path(int x, int y){
    Position pos {x, y};
    this->path.push_back(pos);
}

void Player::remove_last_path(){
    if(!this->path.empty()){
        this->path.pop_back();  // 正确：pop_back() 删除最后一个元素
    }
}

void Player::print_path(){
    if(!this->path.empty()){
        for(auto it = this->path.begin(); it != this->path.end(); ++it){
            std::cout << "x: " << it->x << " y: " << it->y << "    ";
            if((it - this->path.begin()) % 4 == 0 && it != this->path.begin()){
                std::cout << std::endl;
            }
        }
    }
}

MoveCommand::MoveCommand(std::shared_ptr<Player> p, std::shared_ptr<Maze> m, char dir){
    char upper_dir = std::toupper(dir);
    if(upper_dir != 'W' && upper_dir != 'A' && upper_dir != 'S' && upper_dir != 'D'){
        throw std::invalid_argument("无效的移动方向，只支持WASD.");
    }
    this->player = p;
    this->maze = m;
    this->direction = upper_dir;
    this->old_pos = p->get_position();
    this->executed = false;
}

MoveCommand::~MoveCommand(){

}

bool MoveCommand::execute(){
    int new_x = this->player->get_x();
    int new_y = this->player->get_y();
    
    // 根据方向计算新位置
    switch(this->direction){
        case 'W': new_x--; break;
        case 'S': new_x++; break;
        case 'A': new_y--; break;
        case 'D': new_y++; break;
    }
    
    // 检查新位置是否有效
    if(!this->maze->is_valid(new_x, new_y)){
        std::cout << "移动越界！" << std::endl;
        return false;
    }
    
    if(this->maze->is_wall(new_x, new_y)){
        std::cout << "前方是墙壁！" << std::endl;
        return false;
    }
    
    // 执行移动
    this->player->set_position(new_x, new_y, *this->maze);
    this->player->add_to_path(new_x, new_y);
    this->executed = true;
    
    return true;
}

void MoveCommand::undo(){
    if(!this->executed){
        std::cout << "该命令尚未执行，无法撤销" << std::endl;
        return;
    }
    
    this->player->set_position(this->old_pos.x, this->old_pos.y, *this->maze);
    this->player->remove_last_path();
    this->executed = false;
}

CommandHistory::CommandHistory(){
    // 成员变量会自动初始化
}

CommandHistory::~CommandHistory(){
    // 会自动清理
}

void CommandHistory::push(std::shared_ptr<Command> cmd){
    this->history.push(cmd);
}

std::shared_ptr<Command> CommandHistory::pop(){
    if(this->history.empty()){
        return nullptr;
    }
    auto cmd = this->history.top();
    this->history.pop();
    return cmd;
}

bool CommandHistory::is_empty() const {
    return this->history.empty();
}

int CommandHistory::size() const {
    return this->history.size();
}

void CommandHistory::clear(){
    while(!this->history.empty()){
        this->history.pop();
    }
    this->replay_list.clear();
}

void CommandHistory::add_to_replay(std::shared_ptr<Command> cmd){
    this->replay_list.push_back(cmd);
}

MazeGame::MazeGame(const char* maze_file) : game_over(false) {
    this->maze = std::make_shared<Maze>(maze_file);
    this->history = std::make_shared<CommandHistory>();
    
    // 自动查找起点并初始化玩家
    if(!init_player_position()){
        std::cerr << "错误：找不到起点 'S'" << std::endl;
        this->player = std::make_shared<Player>(1, 1);  // 默认位置
    }
}

MazeGame::~MazeGame(){
    // 智能指针会自动清理
}

bool MazeGame::init_player_position(){
    // 遍历迷宫找到起点 'S'
    for(int i = 0; i < this->maze->get_rows(); i++){
        for(int j = 0; j < this->maze->get_cols(); j++){
            if(this->maze->get_maze(i, j) == "S"){
                this->player = std::make_shared<Player>(i, j);
                std::cout << "找到起点: (" << i << ", " << j << ")" << std::endl;
                return true;
            }
        }
    }
    return false;
}

void MazeGame::run(){
    std::cout << "\n==================================================" << std::endl;
    std::cout << "===        欢迎来到迷宫游戏！              ===" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "\n游戏说明：" << std::endl;
    std::cout << "  目标：从起点 S 到达终点 E" << std::endl;
    std::cout << "  '#' - 墙壁（不可通过）" << std::endl;
    std::cout << "  '·' - 可通行路径" << std::endl;
    std::cout << "  'P' - 你的当前位置\n" << std::endl;
    
    std::cout << "命令列表：" << std::endl;
    std::cout << "  W/A/S/D  - 上/左/下/右移动" << std::endl;
    std::cout << "  WWAADD   - 连续移动命令" << std::endl;
    std::cout << "  U        - 撤销上一步移动" << std::endl;
    std::cout << "  P        - 显示完整移动路径" << std::endl;
    std::cout << "  R        - 回放所有移动" << std::endl;
    std::cout << "  SAVE     - 保存当前状态" << std::endl;
    std::cout << "  LOAD     - 恢复上次保存的状态" << std::endl;
    std::cout << "  Q        - 退出游戏" << std::endl;
    std::cout << "==================================================" << std::endl;
    
    // 显示初始状态
    display();
    
    // 主游戏循环
    while(!this->game_over){
        std::cout << "\n请输入命令: ";
        std::string input;
        std::cin >> input;
        
        // 转换为大写便于处理
        std::string cmd = input;
        for(char& c : cmd){
            c = std::toupper(c);
        }
        
        // 处理特殊命令
        if(cmd == "Q" || cmd == "QUIT"){
            std::cout << "\n感谢游玩！再见！" << std::endl;
            break;
        }
        else if(cmd == "P" || cmd == "PATH"){
            print_path();
        }
        else if(cmd == "U" || cmd == "UNDO"){
            undo();
            if(!this->game_over){
                display();
            }
        }
        else if(cmd == "R" || cmd == "REPLAY"){
            replay();
        }
        else if(cmd == "SAVE"){
            save_state();
        }
        else if(cmd == "LOAD"){
            load_state();
        }
        else if(cmd == "H" || cmd == "HELP"){
            // 显示帮助
            std::cout << "\n命令帮助：" << std::endl;
            std::cout << "  W/A/S/D - 移动" << std::endl;
            std::cout << "  U - 撤销, P - 路径, R - 回放" << std::endl;
            std::cout << "  SAVE/LOAD - 保存/加载, Q - 退出" << std::endl;
        }
        else {
            // 处理移动命令（单个或连续）
            int successful_moves = 0;
            for(char c : cmd){
                if(c == 'W' || c == 'A' || c == 'S' || c == 'D'){
                    if(move(c)){
                        successful_moves++;
                        // 每次成功移动后检查是否游戏结束
                        if(this->game_over){
                            break;  // 到达终点，结束循环
                        }
                    } else {
                        // 移动失败，显示当前状态并停止
                        std::cout << "\n第" << (successful_moves + 1) << "步移动失败，已执行前" << successful_moves << "步" << std::endl;
                        if(!this->game_over){
                            display();
                        }
                        break;
                    }
                } else {
                    std::cout << "无效命令: " << c << std::endl;
                    std::cout << "输入 H 查看帮助" << std::endl;
                    if(successful_moves > 0 && !this->game_over){
                        display();
                    }
                    break;
                }
            }
            
            // 如果所有移动都成功，显示最终状态
            if(successful_moves > 0 && !this->game_over){
                display();
            }
        }
    }
    
    if(this->game_over){
        std::cout << "\n游戏结束！" << std::endl;
    }
}

bool MazeGame::process_command(const std::string& cmd_string){
    for(auto it : cmd_string){
        try{
            std::shared_ptr<Command> cmd = std::make_shared<MoveCommand>(this->player, this->maze, it);
            if(cmd->execute()){
                this->history->push(cmd);
                this->history->add_to_replay(cmd);
            } else {
                return false;
            }
        } catch(const std::invalid_argument& e){
            std::cerr << "命令错误: " << e.what() << std::endl;
            return false;
        }
    }
    return true;
}

bool MazeGame::move(char direction){
    try{
        std::shared_ptr<Command> cmd = std::make_shared<MoveCommand>(this->player, this->maze, direction);
        if(cmd->execute()){
            this->history->push(cmd);
            this->history->add_to_replay(cmd);
            this->check_win();
            return true;
        }
        return false;
    } catch(const std::invalid_argument& e){
        std::cerr << "移动错误: " << e.what() << std::endl;
        return false;
    }
}

void MazeGame::undo(){
    if(this->history->is_empty()){
        std::cout << "没有可撤销的操作" << std::endl;
        return;
    }
    std::shared_ptr<Command> cmd = this->history->pop();
    if(cmd){
        cmd->undo();
    }
}

void MazeGame::print_path(){
    std::cout << "\n=== 移动路径 ===" << std::endl;
    this->player->print_path();
    std::cout << "总步数: " << this->player->get_step_count() << std::endl;
}

void MazeGame::replay(){
    std::cout << "\n=== 路径回放 ===" << std::endl;
    const auto& replay_cmds = this->history->get_replay_list();
    
    if(replay_cmds.empty()){
        std::cout << "暂无移动记录" << std::endl;
        return;
    }
    
    std::cout << "移动序列（共 " << replay_cmds.size() << " 步）: ";
    for(size_t i = 0; i < replay_cmds.size(); i++){
        std::cout << replay_cmds[i]->get_type();
        if((i + 1) % 10 == 0 && i != replay_cmds.size() - 1){
            std::cout << "\n                ";
        }
    }
    std::cout << std::endl;
}

void MazeGame::save_state(){
    GameState state(
        this->player->get_position(),
        this->player->get_path(),
        this->player->get_step_count()
    );
    this->saved_states.push(state);
    std::cout << "\n游戏状态已保存！（保存点数量: " << this->saved_states.size() << "）" << std::endl;
}

void MazeGame::load_state(){
    if(this->saved_states.empty()){
        std::cout << "\n没有保存的游戏状态" << std::endl;
        return;
    }
    
    GameState state = this->saved_states.top();
    this->saved_states.pop();
    
    // 恢复玩家位置和路径
    this->player = std::make_shared<Player>(state.player_pos.x, state.player_pos.y);
    // 重建路径
    for(const auto& pos : state.path){
        this->player->add_to_path(pos.x, pos.y);
    }
    
    // 清空当前命令历史（因为状态已回退）
    this->history->clear();
    
    std::cout << "\n游戏状态已恢复！" << std::endl;
    std::cout << "恢复到位置: (" << state.player_pos.x << ", " << state.player_pos.y << ")" << std::endl;
    std::cout << "路径步数: " << state.step_count << std::endl;
    
    display();
}

void MazeGame::check_win(){
    if(this->maze->is_endpoint(this->player->get_x(), this->player->get_y())){
        std::cout << "\n=== 恭喜到达终点！===" << std::endl;
        std::cout << "总步数: " << this->player->get_step_count() << std::endl;
        this->player->print_path();
        this->game_over = true;
    }
}

void MazeGame::display(){
    std::cout << "\n当前迷宫状态:" << std::endl;
    this->maze->print_with_player(this->player->get_x(), this->player->get_y());
    std::cout << "当前位置: (" << this->player->get_x() << ", " << this->player->get_y() << ")" << std::endl;
    std::cout << "已走步数: " << this->player->get_step_count() << std::endl;
}

int main(){
    // 设置控制台为UTF-8编码
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    system("chcp 65001 > nul");  // 强制设置代码页
    
    std::cout << "===============================================" << std::endl;
    std::cout << "===     迷宫游戏 - 主程序                ===" << std::endl;
    std::cout << "===============================================\n" << std::endl;
    
    // 选择迷宫
    std::cout << "请选择迷宫：" << std::endl;
    std::cout << "  1 - Maze1.txt (15x15)" << std::endl;
    std::cout << "  2 - Maze2.txt (21x21)" << std::endl;
    std::cout << "  T - 运行测试程序" << std::endl;
    std::cout << "请输入选择: ";
    
    std::string choice;
    std::cin >> choice;
    
    if(choice == "T" || choice == "t"){
        // 运行测试程序
        std::cout << "\n===============================================" << std::endl;
        std::cout << "===     迷宫游戏功能测试程序              ===" << std::endl;
        std::cout << "===============================================\n" << std::endl;
    
    // ========== 测试1: Maze类基本功能 ==========
    std::cout << "\n【测试1】加载并打印迷宫" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    Maze maze1("Maze1.txt");
    maze1.print();
    
    // ========== 测试2: get_maze功能 ==========
    std::cout << "\n【测试2】测试 get_maze() - 获取指定位置字符" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "位置(0,0): [" << maze1.get_maze(0, 0) << "]" << std::endl;
    std::cout << "位置(1,1): [" << maze1.get_maze(1, 1) << "]" << std::endl;
    std::cout << "位置(1,2): [" << maze1.get_maze(1, 2) << "]" << std::endl;
    std::cout << "位置(1,6): [" << maze1.get_maze(1, 6) << "]" << std::endl;
    
    // ========== 测试3: is_valid功能 ==========
    std::cout << "\n【测试3】测试 is_valid() - 边界检查" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "(5,5)是否有效: " << (maze1.is_valid(5, 5) ? "是" : "否") << std::endl;
    std::cout << "(-1,0)是否有效: " << (maze1.is_valid(-1, 0) ? "是" : "否") << std::endl;
    std::cout << "(100,100)是否有效: " << (maze1.is_valid(100, 100) ? "是" : "否") << std::endl;
    
    // ========== 测试4: is_wall功能 ==========
    std::cout << "\n【测试4】测试 is_wall() - 墙壁检测" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "(0,0)是否是墙: " << (maze1.is_wall(0, 0) ? "是" : "否") << std::endl;
    std::cout << "(1,2)是否是墙: " << (maze1.is_wall(1, 2) ? "是" : "否") << std::endl;
    std::cout << "(1,6)是否是墙: " << (maze1.is_wall(1, 6) ? "是" : "否") << std::endl;
    
    // ========== 测试5: set_maze功能 ==========
    std::cout << "\n【测试5】测试 set_maze() - 修改字符" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "修改前(1,2): [" << maze1.get_maze(1, 2) << "]" << std::endl;
    maze1.set_maze(1, 2, "@");
    std::cout << "修改后(1,2): [" << maze1.get_maze(1, 2) << "]" << std::endl;
    std::cout << "修改后的迷宫:" << std::endl;
    maze1.print();
    
    // 恢复原字符
    maze1.set_maze(1, 2, "·");
    
    // ========== 测试6: print_with_player功能 ==========
    std::cout << "\n【测试6】测试 print_with_player() - 显示玩家位置" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "玩家在位置(5, 5):" << std::endl;
    maze1.print_with_player(5, 5);
    
    // ========== 测试7: Player类功能 ==========
    std::cout << "\n【测试7】测试 Player 类" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    Player player1(1, 1);
    std::cout << "玩家初始位置: (" << player1.get_x() << ", " << player1.get_y() << ")" << std::endl;
    
    // 添加路径
    player1.add_to_path(1, 2);
    player1.add_to_path(2, 2);
    player1.add_to_path(3, 2);
    player1.add_to_path(3, 3);
    std::cout << "添加4个路径点后，路径长度: " << player1.get_step_count() << std::endl;
    std::cout << "当前路径:" << std::endl;
    player1.print_path();
    
    // 删除路径
    player1.remove_last_path();
    std::cout << "\n删除最后一个路径点后，路径长度: " << player1.get_step_count() << std::endl;
    player1.print_path();
    
    // ========== 测试8: MoveCommand异常处理 ==========
    std::cout << "\n【测试8】测试 MoveCommand 异常处理" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    auto test_player = std::make_shared<Player>(5, 5);
    auto test_maze = std::make_shared<Maze>("Maze1.txt");
    
    try {
        std::cout << "创建有效命令 'W': ";
        auto cmd1 = std::make_shared<MoveCommand>(test_player, test_maze, 'W');
        std::cout << "成功" << std::endl;
        
        std::cout << "创建有效命令 'a' (小写): ";
        auto cmd2 = std::make_shared<MoveCommand>(test_player, test_maze, 'a');
        std::cout << "成功" << std::endl;
        
        std::cout << "创建无效命令 'X': ";
        auto cmd3 = std::make_shared<MoveCommand>(test_player, test_maze, 'X');
        std::cout << "成功" << std::endl;
    } catch(const std::invalid_argument& e) {
        std::cout << "捕获异常: " << e.what() << std::endl;
    }
    
    // ========== 测试9: MoveCommand执行和撤销 ==========
    std::cout << "\n【测试9】测试 MoveCommand 执行和撤销" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    auto game_player = std::make_shared<Player>(1, 1);
    auto game_maze = std::make_shared<Maze>("Maze1.txt");
    
    std::cout << "初始位置: (" << game_player->get_x() << ", " << game_player->get_y() << ")" << std::endl;
    
    // 执行向右移动
    try {
        auto move_right = std::make_shared<MoveCommand>(game_player, game_maze, 'D');
        if(move_right->execute()){
            std::cout << "向右移动成功，新位置: (" << game_player->get_x() << ", " << game_player->get_y() << ")" << std::endl;
            
            // 撤销移动
            move_right->undo();
            std::cout << "撤销后位置: (" << game_player->get_x() << ", " << game_player->get_y() << ")" << std::endl;
        }
    } catch(const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }
    
    // ========== 测试10: CommandHistory功能 ==========
    std::cout << "\n【测试10】测试 CommandHistory" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    CommandHistory history;
    
    try {
        auto cmd1 = std::make_shared<MoveCommand>(game_player, game_maze, 'D');
        auto cmd2 = std::make_shared<MoveCommand>(game_player, game_maze, 'S');
        
        history.push(cmd1);
        history.push(cmd2);
        history.add_to_replay(cmd1);
        history.add_to_replay(cmd2);
        
        std::cout << "历史栈大小: " << history.size() << std::endl;
        std::cout << "回放列表大小: " << history.get_replay_list().size() << std::endl;
        
        auto popped = history.pop();
        std::cout << "弹出一个命令后，历史栈大小: " << history.size() << std::endl;
        
        history.clear();
        std::cout << "清空后，历史栈大小: " << history.size() << std::endl;
        std::cout << "清空后，回放列表大小: " << history.get_replay_list().size() << std::endl;
    } catch(const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }
    
    // ========== 测试11: MazeGame简单测试 ==========
    std::cout << "\n【测试11】测试 MazeGame 基本功能" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    try {
        MazeGame game("Maze1.txt");
        std::cout << "MazeGame创建成功" << std::endl;
        std::cout << "游戏是否结束: " << (game.is_game_over() ? "是" : "否") << std::endl;
        
        // 测试display
        game.display();
        
        // 测试移动
        std::cout << "\n尝试向右移动..." << std::endl;
        if(game.move('D')){
            std::cout << "移动成功" << std::endl;
            game.display();
        }
        
        // 测试撤销
        std::cout << "\n尝试撤销..." << std::endl;
        game.undo();
        game.display();
        
    } catch(const std::exception& e) {
        std::cerr << "MazeGame测试错误: " << e.what() << std::endl;
    }
    
    // ========== 测试12: 加载Maze2 ==========
    std::cout << "\n【测试12】加载 Maze2.txt" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    Maze maze2("Maze2.txt");
    maze2.print();
    
    std::cout << "\n===============================================" << std::endl;
    std::cout << "===            测试完成！                  ===" << std::endl;
    std::cout << "===============================================" << std::endl;
    } 
    else if(choice == "1"){
        // 启动 Maze1 游戏
        try{
            MazeGame game("Maze1.txt");
            game.run();
        } catch(const std::exception& e){
            std::cerr << "游戏错误: " << e.what() << std::endl;
        }
    }
    else if(choice == "2"){
        // 启动 Maze2 游戏
        try{
            MazeGame game("Maze2.txt");
            game.run();
        } catch(const std::exception& e){
            std::cerr << "游戏错误: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "无效选择！" << std::endl;
    }
    
    return 0;
}