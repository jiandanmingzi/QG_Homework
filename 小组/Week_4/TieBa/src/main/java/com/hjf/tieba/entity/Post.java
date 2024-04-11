package com.hjf.tieba.entity;

import java.time.LocalDateTime;
import java.util.ArrayList;

public class Post {
    public int PostId;
    public String title;
    public User poster;
    public LocalDateTime postTime;
    public LocalDateTime RecentReplyTime;
    public String content;
    public Forum forum;
    public ArrayList<Comment> comments;
    public int likes;
    public int floors;
}
