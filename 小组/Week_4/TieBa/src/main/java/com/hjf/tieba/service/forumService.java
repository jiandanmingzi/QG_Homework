package com.hjf.tieba.service;

import com.hjf.tieba.entity.Forum;
import com.hjf.tieba.util.CRUD_Utils;

import java.util.ArrayList;
import java.util.List;

public interface forumService {
    public List<Forum> getAllForumList();
    public Forum getForum(int forumId);
    public int updateForum(int forumId,String forumName,String Introduction);
}
