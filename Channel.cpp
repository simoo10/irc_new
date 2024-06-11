#include "Channel.hpp"
#include "Server.hpp"

void	createChannel(string av[2], Channel &ch, string username, int fd){
	if (av[0][0] != '#'){
		string toSend = "Invalid channel name\r\n";
		send(fd, toSend.c_str(), toSend.size(), 0);
	}
	else{
		//av[0] = av[0].erase(0, 1);
		// av[0] = av[0].substr(0, av[0].size() - 1);
		std::cout<<"channel name==>>"<<(int)av[0][4]<<std::endl;
		std::cout << "Creating channel==>>: " << av[0] <<std::endl;
		std::cout<<"channel name size==>>"<<av[0].size()<<std::endl;
		if (ch.hasChannel(av[0])){
			if (ch.getInviteOnly(av[0])){
				if (!ch.isInvited(av[0], username)){
					string toSend = "You are not invited to this channel\r\n";
					send(fd, toSend.c_str(), toSend.size(), 0);
				}
				else
					ch.addUser(av[0], username, fd);
			}
			else if (ch.getUserLimit(av[0]) != -1 && ch.getUserList(av[0]).size() >= ch.getUserLimit(av[0])){
				string toSend = "Channel is full\r\n";
				send(fd, toSend.c_str(), toSend.size(), 0);
			}
			else if (ch.isKeyRequired(av[0])){
				if (av[1] != ch.getChannelKey(av[0])){
					string toSend = "Invalid channel key\r\n";
					send(fd, toSend.c_str(), toSend.size(), 0);
				}
				else
					ch.addUser(av[0], username, fd);
			}
			else
				ch.addUser(av[0], username, fd);
		}
		else{
			if (!ch.addChannel(av[0], username, fd)){

				string toSend = "Channel already exists\r\n";
				send(fd, toSend.c_str(), toSend.size(), 0);
			}
			else
			{
				//send_message(t.socket_fd,  ":" + t.nickName + "!" + t.serverName + "@localhost JOIN :"+ channel + "\r\n");
				//send_message(t.socket_fd , ":localhost 353 " + t.nickName + " = " + channel + " :@" + t.nickName + "\r\n"); 
    			//send_message(t.socket_fd, ":localhost 366 " + t.nickName + " " + channel + " :End of /NAMES list.\r\n");
				string toSend = ":" + username + "!" + username +"@localhost JOIN :" + av[0] + "\r\n";
				string toSend2 = ":localhost 353 " + username + " = " + av[0] + " :@" + username + "\r\n";
				string toSend3 = ":localhost 366 " + username + " " + av[0] + " :End of /NAMES list.\r\n";
				send(fd, toSend.c_str(), toSend.size(), 0);
				send(fd, toSend2.c_str(), toSend2.size(), 0);
				send(fd, toSend3.c_str(), toSend3.size(), 0);
			}
		}
	}
}

