// 00 离开服务器
// 00 id
// 
// 01 加入服务器
// 01 name passwd
// 
// 02 发送消息
// 02 msg
// 
// 11 准许加入并分配id
// 11 id
// 
// 12 密码错误，拒绝加入
// 12 wrong_pass
//

const char* LeaveServer = "00";
const char* JoinServer = "01";