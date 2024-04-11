package com.hjf.tieba.service.Impl;

import com.hjf.tieba.entity.Forum;
import com.hjf.tieba.service.forumService;
import com.hjf.tieba.util.CRUD_Utils;

import java.util.ArrayList;
import java.util.List;

public class forumServiceImpl implements forumService {
    @Override
    public List<Forum> getAllForumList(){
        String sql="SELECT * FROM forum";
        return CRUD_Utils.query(sql, rs -> {
            List<Forum> forums = new ArrayList<>();
            while(rs.next()) {
                Forum forum = new Forum();
                forum.forumId = rs.getInt("id");
                forum.forumName = rs.getString("name");
                forum.Introduction = rs.getString("Introduction");
                forum.follow = rs.getInt("follow");
                forum.FoundTime = rs.getTimestamp("created_at");
                forum.UpdatedTime = rs.getTimestamp("updated_at");
                forums.add(forum);
            }
            return forums;
        });
    }
    @Override
    public Forum getForum(int forumId){
        String sql="SELECT * FROM forum WHERE id=?";
        return CRUD_Utils.query(sql, rs -> {
            if(rs.next()) {
                Forum forum = new Forum();
                forum.forumId = rs.getInt("id");
                forum.forumName = rs.getString("name");
                forum.Introduction = rs.getString("Introduction");
                forum.follow = rs.getInt("follow");
                forum.FoundTime = rs.getTimestamp("created_at");
                forum.UpdatedTime = rs.getTimestamp("updated_at");
                return forum;
            }
            return null;
        }, forumId);
    }
    @Override
    public int updateForum(int forumId,String forumName,String Introduction){
        String sql="UPDATE forum SET name=?,Introduction=? WHERE id=?";
        return CRUD_Utils.update(sql,forumName,Introduction,forumId);
    }
    public forumServiceImpl(){
    }
}
