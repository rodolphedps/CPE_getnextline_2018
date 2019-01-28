/*
** EPITECH PROJECT, 2019
** get_next_line
** File description:
** get_next_line.c
*/

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int my_strlen(char *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    while (str[i] != '\0')
        i++;
    return (i);
}

char *get_new_alloc(char *buf, char *res)
{
    char *ret;
    int a = 0;
    int b = 0;

    if (!buf && !res)
        return (NULL);
    ret = malloc(sizeof(char) * (my_strlen(res) + my_strlen(buf) + 1));
    if (!ret)
        return (NULL);
    if (res != NULL) {
        while (res[a] != '\0') {
            ret[a] = res[a];
            a++;
        }
    }
    if (buf != NULL) {
        for (; buf[b] != '\0'; a++, b++)
            ret[a] = buf[b];
    }
    ret[my_strlen(buf) + my_strlen(res)] = '\0';
    return (ret);
}

int find_n(char *res)
{
    int x = 0;

    if (res == NULL)
        return (0);
    while (res[x] != '\0') {
        if (res[x] == '\n')
            return (1);
        x++;
    }
    return (0);
}

char *str_dup_by_size(char *res, int size)
{
    char *ret2 = malloc(sizeof(char) * size + 1);
    int x = 0;

    if (!ret2)
        return (NULL);
    while (res[x] != '\0' && x < size) {
        ret2[x] = res[x];
        x++;
    }
    ret2[size] = '\0';
    return (ret2);
}

char *get_next_line(int fd)
{
    static char *buff = NULL;
    char *res = NULL;
    char buf[READ_SIZE + 1];
    int i = 0;
    int rd = 0;

    if (fd == -1)
        return (NULL);
    res = get_new_alloc(buff, res);
    buff = NULL;
    while (find_n(res) != 1) {
        rd = read(fd, buf, READ_SIZE);
        buf[READ_SIZE] = '\0';
        if (rd == -1 || buf[0] == '\0')
            return (NULL);
        if (rd == 0)
            return (res);
        res = get_new_alloc(buf, res);
    }
    while (res[i] != '\n' && res[i] != '\0')
        i++;
    buff = str_dup_by_size(res + i + 1, my_strlen(res + i + 1));
    res = str_dup_by_size(res, i);
    return (res);
}