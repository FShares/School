package com.sax;

import javax.xml.parsers.*;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
public class test {
	//使用SAXophone技术解析XML文件- saxclass.xml
	public static void main(String[] args) throws Exception, SAXException {
		//创建 SaxParserFactory
		SAXParserFactory spf = SAXParserFactory.newInstance();
		//创建 SaxParser解析器
		SAXParser saxParser = spf.newSAXParser();
		//把XML文件和事件处理对象关联
		saxParser.parse("src/saxclass.xml", new MyHandler());
	}
}

//继承事件处理类
class MyHandler extends DefaultHandler{
	//结束文档
	public void endDocument() throws SAXException {
		// TODO Auto-generated method stub
		System.out.println("结束文档");
		super.endDocument();
	}
	//结束元素
	public void endElement(String arg0, String arg1, String arg2)
			throws SAXException {
		// TODO Auto-generated method stub
		super.endElement(arg0, arg1, arg2);
	}
	//XML中文本
	public void characters(char[] arg0, int start, int length)
			throws SAXException {
		// TODO Auto-generated method stub
		super.characters(arg0, start, length);
		//显示文本内容
		//System.out.println(arg0+"start: "+start+"length: "+length);
		String con =new String(arg0,start,length);
		if(!con.trim().equals("")){//有无空行
			System.out.println(new String (arg0,start,length));
		}
		
	}
	//发现文档开始
	public void startDocument() throws SAXException {
		// TODO Auto-generated method stub
		System.out.println("发现文档开始");
		super.startDocument();
	}
	//开始一个元素
	public void startElement(String arg0, String arg1, String arg2,
			Attributes arg3) throws SAXException {
		// TODO Auto-generated method stub
		System.out.println("元素名称="+arg2);
		super.startElement(arg0, arg1, arg2, arg3);
	}
}