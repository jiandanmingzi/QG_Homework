package com.hjf.tieba.entity;

import java.time.LocalDateTime;

public class Reply {
    public int ReplyId;
    public User replyer;
    public LocalDateTime replyTime;
    public String content;
    public Comment comment;
    public int likes;
}
