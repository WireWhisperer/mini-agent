#include "command.h"

extern WINDOW *win_commu_box;
extern WINDOW *win_commu_data;
extern WINDOW *win_state;
extern WINDOW *win_input;

void react_to_input(char* buffer)
{
    char *ptr = NULL;
    if (!strcmp(buffer, "/exit")) 
    {
        destroy_win(win_commu_box);
        destroy_win(win_commu_data);
        destroy_win(win_state);
        destroy_win(win_input);
        endwin();
        exit(0);
    }
    else if ((ptr = strstr(buffer, "/read"))) 
    {
        commond_Read(ptr);
    }
    else
    {
        wprintw(win_commu_data, "Assistant:\n ## `429` Too many Requests\n\n**The server is busy, please try again later.**\n\n");
        wrefresh(win_commu_data);
    }
}

void commond_Read(char* ptr)
{
    ptr += 6; 
    char file_addr[50];  //存储文件地址
    //bool file_addr_flag = true;
    int row_read;  //存储读取的行数
    bool row_read_flag = true;
    int row_true;  //存储实际读取的行数

    //读取地址
    while (*ptr == ' ') ptr++; //跳过空白
    int count = 0;
    while (*ptr != ' ')
    {
        file_addr[count] = *ptr;
        ptr++;
        count++;
    }
    file_addr[count] = '\0'; // 添加字符串结束符
    
    //读取行数
    count = 0;
    while (*ptr == ' ')
    {
        if (count > 10)
        {
            row_read_flag = false;
            break;
        } 
        ptr++;
        count++;
    }
    if (row_read_flag) row_read = atoi(ptr); //获取读取的行数
    
    wprintw(win_commu_data, "Assistant:\n Tool_Use [read_file] file=%s\n\n", file_addr);
    wrefresh(win_commu_data);

    //打开地址核验
    FILE *file = fopen(file_addr, "r");
    if (file == NULL)
    {
        wprintw(win_commu_data, "%s read not found\n\n", file_addr);
        wrefresh(win_commu_data);
        fclose(file);
        return;
    }
    else
    {
        while(!feof(file))
        {
            char flag = fgetc(file);
            if(flag == '\n')
            count++;
        }
        row_true = count + 1; //加上最后一行

        if ( (row_true > 100 && !row_read_flag) || (row_true > 500 && row_read_flag) )
        {
            wprintw(win_commu_data, "Assistant:\n Reading failed due to too many lines in the file\n\n");
            wrefresh(win_commu_data);
        }
        else
        {
            long read_row_num = 0; //已经读取的行数
            while(!feof(file))
            {
                char flag = fgetc(file);
                waddch(win_commu_data, flag);
                if (read_row_num > row_read && row_read_flag) break;
                if(flag == '\n') read_row_num++;
                refresh();
            }
            
        }
        fclose(file);
    }
}