package com.hjf.tieba.controller;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import com.hjf.tieba.entity.Forum;
import com.hjf.tieba.service.Impl.UserServiceImpl;
import com.hjf.tieba.service.Impl.forumServiceImpl;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.util.List;

@WebServlet("/myselfServlet")
public class myselfServlet extends HttpServlet {
    private final forumServiceImpl forumService = new forumServiceImpl();
    private final UserServiceImpl userService = new UserServiceImpl();
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws javax.servlet.ServletException, java.io.IOException {
        List<Forum> forums = forumService.getAllForumList();
        String jsonString = JSON.toJSONString(forums);
        response.setContentType("application/json;charset=utf-8");
        response.getWriter().write(jsonString);
    }
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws javax.servlet.ServletException, java.io.IOException {
        StringBuilder string = new StringBuilder();
        try(BufferedReader reader = request.getReader()){
            String line;
            while((line = reader.readLine())!= null){
                string.append(line).append('\n');
            }
        }
        JSONObject jsonString = JSON.parseObject(string.toString());
        int forumId = jsonString.getInteger("forumId");
        String forumName = jsonString.getString("forumName");
        String introduction = jsonString.getString("introduction");
        int result = forumService.updateForum(forumId, forumName, introduction);
        JSONObject jsonResponse = new JSONObject();
        if(result>0)
            jsonResponse.put("status", "success");
        else
            jsonResponse.put("status", "fail");
        response.setContentType("application/json;charset=utf-8");
        response.getWriter().write(jsonResponse.toString());
    }
}
