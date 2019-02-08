#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>

#define PORTNUM 15000

main(int argc, char **argv)
{
    int s, ns;
    int ppid;
    int nport;
    struct sockaddr_in serv_addr, clnt_addr;
    struct hostent *hp;
    char buf[80], hname[80];

    nport = PORTNUM;
    nport = htons((u_short)nport);
    
    if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error in socket() call"); exit(1);
    }

    bzero(&serv_addr, (size_t)sizeof(serv_addr));
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    serv_addr.sin_port = nport;
    if(bind(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror(" Error in bind() call"); exit(1);
    }


    fprintf(stderr, "Server ready: %s\n", inet_ntoa(serv_addr.sin_addr));

 /*
  listen - информирует систему о том, что сервер готов принимать запросы
               (т.е. просит организовать очередь для запросов к серверу)

      #include 
      int listen(int s, int backlog);

      s       - дескриптор гнезда
      backlog - желаемое значение длины очереди 
 */
    if(listen(s, 5) == -1)
    {
        perror("Error in listen() call"); exit(1);
    }

    while(1)
    {
        int addrlen, pid;

        bzero(&clnt_addr, sizeof(clnt_addr));
        addrlen = sizeof(clnt_addr);

/*
  accept - извлекает первый запрос из очереди запросов на 
               соединение и создает для него коммуникационное гнездо

      #include 
      int accept(int s, void *addr, int *addrlen);

      s       - дескриптор гнезда
      addr    - указатель структуры, в которую будет записан адрес клиента,
                с которым устанавливается соединение
      addrlen - размер адр. структуры 

      при успешном выполнении возвращает неотрицательное число,
      которое является дескриптором установленного соединения от
      принятого запроса.
      -1 при ошибке (устанавливается errno)

*/
        if((ns = accept(s, (struct sockaddr *)&clnt_addr, &addrlen)) == -1)
        {
            perror("Error in accept() call"); exit(1);
        }

        fprintf(stderr, "Client @ %s\n", inet_ntoa(clnt_addr.sin_addr));


// Создание дочернего процесса для организации связи с клиентом 

        if((pid = fork()) == -1)
        {
            perror("Error in fork() call"); exit(1);
        }
        if(!pid)
        {
       int nbytes;
            int fout;
            close(s);
   
/*
recv - прием сообщения от гнезда

      #include 

      int recv(int s, void *buf, int len, int flags);

      s - дскриптор гнезда

      buf - указатель на буфер, в который принимается сообщение

      len - размер буфера


      recv(), recvfrom() возвращает:

            n   успешное завершение - длина принятого сообщения
            0   гнездо блокировано
           -1   ошибка (устанавливается  errno)


*/
       while((nbytes = recv(ns, buf, sizeof(buf), 0)) != 0)
       {
      if(!strcmp("terminate", buf))
      {
          pid_t  ppid = getppid();
          if(kill(ppid, SIGKILL) == -1)
          {
         perror("Shutdown request failed");
#define FAILED "Failed to shut the server down.\n"
         send(ns, FAILED, strlen(FAILED) + 1, 0);
          }
          else
          {           
         fprintf(stderr, "Server has been shut down...\n");
#define OK "Server has been shut down.\n"
         send(ns, OK, strlen(OK) + 1, 0);
          }   
      }
      else
/*
send() - отправить сообщение

      #include 

      int send(int s, const void *msg, int len, int flags);

      s - дескриптор гнезда
      msg - указатель на буфер с сообщением
      len - длина сообщения
      flags:
   MSG_OOB - экстренные данные

      send(), sendto() возвращают:

            n   успешное завершение, передано n байтов
           -1   ошибка (устанавливается  errno)

*/
          send(ns, buf, sizeof(buf), 0);
       }
           close(ns);
       exit(0);
        }
        close(ns);
    }
}
