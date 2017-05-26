package com.hsp;

import javax.xml.parsers.*;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class DomXML {

//使用DOM对XML进行CRUD操作
	
	public static void main(String[] args) throws Exception{
		// TODO Auto-generated method stub
		//创建一个DocumentBuilderFactory
		DocumentBuilderFactory dbf=DocumentBuilderFactory.newInstance();
		//创建一个DocumentBuilderFactory，得到一个DocumentBuilder对象
		DocumentBuilder dBuilder=dbf.newDocumentBuilder();
		//指定要去解析哪一个XML文件
		Document document=dBuilder.parse("src/class.xml");
		//System.out.println(document);
		list(document);
		
	}
	//遍历该XML文件
	public static void list(Node node){
		if(node.getNodeType()==node.ELEMENT_NODE){
		System.out.println("名称"+node.getNodeName());
		}
		//取node的子节点
		NodeList nodelist=node.getChildNodes();
		for(int i=0;i<nodelist.getLength();i++){
			//再去显示
			Node n=nodelist.item(i);
			list(n);
		}
	}

}
