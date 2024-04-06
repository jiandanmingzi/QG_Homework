package com.hjf.tieba.entity;

import java.time.LocalDateTime;
import java.util.ArrayList;

/**
    *用户实体类
 */
public class User {
    /**
     * 用户的唯一标识符。
     */
    public int Id;
    /**
     * 用户的帐号。
     */
    public String account;
    /**
     * 用户的用户名。
     */
    public String userName;
    /**
     * 用户创建日期。
     */
    public LocalDateTime CreatedDate;
    /**
     * 用户创建的论坛列表。
     */
    public ArrayList<Forum> MyForum;
    /**
     * 用户发布的帖子列表。
     */
    public ArrayList<Post> MyPost;
    /**
     * 用户发布的评论列表。
     */
    public ArrayList<Comment> MyComment;
    /**
     * 用户发布的回复列表。
     */
    public ArrayList<Reply> MyReply;
    /**
     * 用户关注的论坛列表。
     */
    public ArrayList<Forum> FollowForum;
    /**
     * 用户点赞的帖子列表。
     */
    public ArrayList<Post> likePost;
    /**
     * 用户的被点赞数。
     */
    public int likes;
    public User() {
    }

}
