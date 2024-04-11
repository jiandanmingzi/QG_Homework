package com.hjf.tieba.entity;

import java.time.LocalDateTime;
import java.util.ArrayList;

public class Comment {
    public int CommentId;
    public User Commenter;
    public LocalDateTime commentTime;
    public String content;
    public Post post;
    public ArrayList<Reply> replies;
    public int likes;
    public int floor;
}
