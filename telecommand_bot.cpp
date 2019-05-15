#include <stdio.h>
#include <stdlib.h>
#include <tgbot/tgbot.h>

int main() {
    TgBot::Bot bot("644444212:AAG9Qhi_02cvN89wXftkavRaHaiV2Q9tdA4");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Welcome to Telegram-Command-Bot. \n This allows to run linux command on server and retrieve the output");
    });
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("New Command >>  %s\n", message->text.c_str());

        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }

        FILE *fp;
        char path[1035];
        /* Open the command for reading. */
        fp = popen(message->text.c_str(), "r");
        if (fp == NULL) {
            printf(">>> Failed to run command\n" );
            return;
        }

        /* Read the output a line at a time - output it. */
        std::string result_str;
        while (fgets(path, sizeof(path)-1, fp) != NULL) {
            printf(">>> %s", path);

            std::string str(path);
            result_str += str + "\n";
	    //if(!str.empty())
		//bot.getApi().sendMessage(message->chat->id, str);
        }

        if(!result_str.empty()){
            bot.getApi().sendMessage(message->chat->id, result_str);
        }else {
            bot.getApi().sendMessage(message->chat->id, "Not found");
        }
        /* close */
        pclose(fp);
        //bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}
