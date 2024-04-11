package com.hjf.tieba.entity;

import java.sql.Timestamp;
import java.util.ArrayList;

public class Forum {
    public int forumId;
    public String forumName;
    public User owner;
    public Timestamp FoundTime;
    public Timestamp UpdatedTime;
    public String Introduction;
    public ArrayList<Post> Posts;
    public int follow;
    public Forum() {}
}
