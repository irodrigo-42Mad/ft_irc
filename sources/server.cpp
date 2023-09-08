/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:44:29 by icastell          #+#    #+#             */
/*   Updated: 2023/09/08 16:01:34 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/IRC_Headers.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


//#define SERV_PORT "9034"   // SERV_ADDR we're listening on

void my_leaks(void)
{
    system ("leaks ircserv");
}

// Get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// Return a listening socket
int get_listener_socket(void)
{
    int listener;     // Listening socket descriptor
    int yes=1;        // For setsockopt() SO_REUSEADDR, below
    int rv;

    struct addrinfo hints, *res, *p;

    // Get us a socket and bind it
    memset(&hints, 0, sizeof hints);
    hints.ai_flags = AI_PASSIVE;		//fill in my IP for me
    hints.ai_family = AF_UNSPEC;		//don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;	//TCP stream sockets
    if ((rv = getaddrinfo(NULL, SERV_ADDR, &hints, &res)) != 0) {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        exit(1);
    }
    
    for(p = res; p != NULL; p = p->ai_next) {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0) { 
            continue;
        }
        
        // Lose the pesky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }

    // If we got here, it means we didn't get bound
    if (p == NULL) {
        return -1;
    }

    freeaddrinfo(res); // All done with this

    // Listen
    if (listen(listener, 10) == -1) {
        return -1;
    }

    return listener;
}

// // tratamiento de memoria nueva ft_realloc
// size_t ft_malloc_usable_size(void* ptr) {
//     if (ptr == NULL) {
//         return 0; // Si el puntero es nulo, no hay tamaño útil
//     }

//     void* end = sbrk(0); // Obtener la ubicación actual del final del heap
//     void* start = ptr;   // Puntero al comienzo del bloque asignado

//     // Calcular el tamaño aproximado del bloque asignado
//     size_t size = (size_t)((char*)end - (char*)start);

//     return size;
// }

void* ft_realloc(void* ptr, size_t new_size) {
    if (new_size == 0) {
        // Si el nuevo tamaño es 0, es equivalente a liberar la memoria
        free(ptr);
        return NULL;
    }

    if (ptr == NULL) {
        // Si el puntero original es nulo, simplemente asigna nueva memoria
        return malloc(new_size);
    } else {
        // Asigna nueva memoria del tamaño especificado
        void* new_ptr = malloc(new_size);

        if (new_ptr == NULL) {
            return NULL; // Manejo de error: no se pudo asignar memoria
        }

        // Copia los datos del bloque de memoria original al nuevo
        //size_t old_size = malloc_usable_size(ptr); // Tamaño del bloque original
        size_t old_size = sizeof(ptr);//ft_malloc_usable_size(ptr); // Tamaño del bloque original
        size_t copy_size = (new_size < old_size) ? new_size : old_size;

        memcpy(new_ptr, ptr, copy_size);

        // Libera el bloque de memoria original
        free(ptr);

        return new_ptr;
    }
}

// Add a new file descriptor to the set
void add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size)
{
    // If we don't have room, add more space in the pfds array
    if (*fd_count == *fd_size) {
        *fd_size *= 2; // Double it

        *pfds = (pollfd *) ft_realloc(*pfds, sizeof(**pfds) * (*fd_size));
        //*pfds = realloc(*pfds, sizeof(**pfds) * (*fd_size));
    }

    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN; // Check ready-to-read

    (*fd_count)++;
}

// Remove an index from the set
void del_from_pfds(struct pollfd pfds[], int i, int *fd_count)
{
    // Copy the one from the end over this one
    pfds[i] = pfds[*fd_count-1];

    (*fd_count)--;
}

// Main
int main(int argc, char** argv)
{
    int listener;     // Listening socket descriptor

    int newfd;        // Newly accept()ed socket descriptor
    struct sockaddr_storage remoteaddr; // Client address
    socklen_t addrlen;

    char buf[256];    // Buffer for client data

    char remoteIP[INET6_ADDRSTRLEN];

    // Start off with room for 5 connections
    // (We'll realloc as necessary)
    int fd_count = 0;
    int fd_size = 5;
    (void) argc;
 
    if (std::strcmp(argv[0], "./ircserv") != 0)
    {
        std::cerr << "APP name is not correct, cannot run" << std::endl;
        exit (-1); 
    }




    //ircserv irc ( port, name, host, paswd);

    
    
    struct pollfd *pfds = (pollfd *) malloc(sizeof *pfds * fd_size); //pfds es la matriz de información: qué sockets monitorear y para qué.
    atexit (my_leaks);
    // Set up and get a listening socket
    listener = get_listener_socket();

    if (listener == -1) {
        fprintf(stderr, "error getting listening socket\n");
        exit(1);
    }

    // Add the listener to set
    pfds[0].fd = listener;
    pfds[0].events = POLLIN; // ReSERV_ADDR ready to read on incoming connection

    fd_count = 1; // For the listener

    // Main loop
    while (42){
        int poll_count = poll(pfds, fd_count, -1);
        if (poll_count == -1) {
            perror("poll");
            exit(1);
        }

        // Run through the existing connections looking for data to read
        for(int i = 0; i < fd_count; i++) {

            // Check if someone's ready to read
            if (pfds[i].revents & POLLIN) { // We got one!!

                if (pfds[i].fd == listener) {
                    // If listener is ready to read, handle new connection

                    addrlen = sizeof remoteaddr;
                    newfd = accept(listener,
                        (struct sockaddr *)&remoteaddr,
                        &addrlen);

                    if (newfd == -1) {
                        perror("accept");
                    } else {
                        add_to_pfds(&pfds, newfd, &fd_count, &fd_size);

                        printf("pollserver: new connection from %s on "
                            "socket %d\n",
                            inet_ntop(remoteaddr.ss_family,
                                get_in_addr((struct sockaddr*)&remoteaddr),
                                remoteIP, INET6_ADDRSTRLEN),
                            newfd);
                    }
                } else {
                    // If not the listener, we're just a regular client
                    int nbytes = recv(pfds[i].fd, buf, sizeof buf, 0);

                    int sender_fd = pfds[i].fd;

                    if (nbytes <= 0) {
                        // Got error or connection closed by client
                        if (nbytes == 0) {
                            // Connection closed
                            printf("pollserver: socket %d hung up\n", sender_fd);
                        } else {
                            perror("recv");
                        }

                        close(pfds[i].fd); // Bye!

                        del_from_pfds(pfds, i, &fd_count);

                    } else {
                        // We got some good data from a client

                        
                        for(int j = 0; j < fd_count; j++) {
                            // Send to everyone!
                            int dest_fd = pfds[j].fd;

                            // Except the listener and ourselves
                            if (dest_fd != listener && dest_fd != sender_fd) {
                                if (send(dest_fd, buf, nbytes, 0) == -1) {
                                    perror("send");
                                }
                            }
                        }
                    }
                } // END handle data from client
            } // END got ready-to-read from poll()
        } // END looping through file descriptors
    } // END for(;;)--and you thought it would never end!
    
    return 0;
}
