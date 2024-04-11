package com.hjf.tieba.controller;

import com.alibaba.fastjson.JSONObject;
import com.hjf.tieba.entity.User;
import com.hjf.tieba.service.Impl.UserServiceImpl;
import com.hjf.tieba.service.UserService;
import com.hjf.tieba.util.JSON_Utils;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/userServlet")
public class UserServlet extends BaseServlet{
    private final UserService userService = new UserServiceImpl();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        super.doGet(req, resp);
    }

    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        super.doPost(req, resp);
    }

    public void login(HttpServletRequest req, HttpServletResponse resp, JSONObject jsonString) throws IOException {
        resp.setContentType("application/json");
        String userAccount = jsonString.getString("userAccount");
        String passWord = jsonString.getString("passWord");
        User user = userService.login(passWord,userAccount);
        if (user!= null) {
            HttpSession session = req.getSession();
            session.setAttribute("user", user);
            resp.setStatus(301);
            resp.sendRedirect("http://localhost:8080/TieBa/home.html");
        } else {
            PrintWriter out = resp.getWriter();
            out.println("{\"success\": false, \"message\": \"用户名或密码错误\"}");
        }
    }

    public void signup(HttpServletRequest req, HttpServletResponse resp, JSONObject jsonString) throws IOException {
        resp.setContentType("application/json");
        String userAccount = jsonString.getString("userAccount");
        String passWord = jsonString.getString("passWord");
        String userName = "default";
        if (userService.signup(passWord,userAccount,userName)){
            resp.sendRedirect("login.html");
        }else {
            PrintWriter out = resp.getWriter();
            out.println("{\"success\": false, \"message\": \"注册失败(请尝试更改用户名或账号)\"}");
        }
    }

    public void checkAccount(HttpServletRequest req, HttpServletResponse resp, JSONObject jsonString) throws IOException {
        resp.setContentType("application/json");
        String userAccount = jsonString.getString("userAccount");
        if (userService.checkAccount(userAccount)){
            PrintWriter out = resp.getWriter();
            out.println("{\"success\": false, \"message\": \"该账号已被注册\"}");
        }
    }
}
