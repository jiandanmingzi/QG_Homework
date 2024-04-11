package com.hjf.tieba.util;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;

import javax.servlet.http.HttpServletRequest;
import java.io.BufferedReader;
import java.io.IOException;

public class JSON_Utils {
    public static JSONObject RequetToJsonString(HttpServletRequest req) throws IOException {
        StringBuffer sb = new StringBuffer();
        BufferedReader br = req.getReader();
        String line;
        while ((line = br.readLine())!= null) {
                sb.append(line).append("\n");
        }
        return JSON.parseObject(sb.toString());
    }
}
