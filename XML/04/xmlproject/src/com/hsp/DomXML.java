package com.hsp;

import javax.xml.parsers.*;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class DomXML {

//ʹ��DOM��XML����CRUD����
	
	public static void main(String[] args) throws Exception{
		// TODO Auto-generated method stub
		//����һ��DocumentBuilderFactory
		DocumentBuilderFactory dbf=DocumentBuilderFactory.newInstance();
		//����һ��DocumentBuilderFactory���õ�һ��DocumentBuilder����
		DocumentBuilder dBuilder=dbf.newDocumentBuilder();
		//ָ��Ҫȥ������һ��XML�ļ�
		Document document=dBuilder.parse("src/class.xml");
		//System.out.println(document);
		list(document);
		
	}
	//������XML�ļ�
	public static void list(Node node){
		if(node.getNodeType()==node.ELEMENT_NODE){
		System.out.println("����"+node.getNodeName());
		}
		//ȡnode���ӽڵ�
		NodeList nodelist=node.getChildNodes();
		for(int i=0;i<nodelist.getLength();i++){
			//��ȥ��ʾ
			Node n=nodelist.item(i);
			list(n);
		}
	}

}
