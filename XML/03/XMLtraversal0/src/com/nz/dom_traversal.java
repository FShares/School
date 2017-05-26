package com.nz;

import javax.xml.parsers.*;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class dom_traversal {
	
	//使用DOM进行XML文件遍历
	public static void main(String[] args) throws Exception{
		// TODO Auto-generated method stub
       //创建一个DocumentBuilderFactory
		DocumentBuilderFactory dbf=DocumentBuilderFactory.newInstance();
		//通过DocumentBuilderFactory工厂实例得到一个解析器
		DocumentBuilder dBuilder=dbf.newDocumentBuilder();
		//指定需要解析的XML文件
		Document document=dBuilder.parse("src/class.xml");
		//list(document);
		read(document);
		
	}
	//显示第一个学生的信息
	//如何取出属性值
	public static void read(Document doc){
		NodeList nl=doc.getElementsByTagName("学生");
		//取出第一个学生
		Element stu=(Element) nl.item(0);
		System.out.println("学生学号："+stu.getAttribute("id"));
		Element name=(Element) stu.getElementsByTagName("名字").item(0);
		System.out.println(name.getTextContent());
		}
	//遍历该XML文件
	public static void list(Node node){
		if(node.getNodeType()==node.ELEMENT_NODE)
		{
		System.out.println("节点名称："+node.getNodeName());
		}
		//取出node的子节点
		NodeList nodelist=node.getChildNodes();
		//进行遍历
		for(int i=0;i<nodelist.getLength();i++){
			//再去显示
			Node n=nodelist.item(i);
			list(n);
		}
	}

}
