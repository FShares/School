package com.nz;

import javax.xml.parsers.*;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class dom_traversal {
	
	//ʹ��DOM����XML�ļ�����
	public static void main(String[] args) throws Exception{
		// TODO Auto-generated method stub
       //����һ��DocumentBuilderFactory
		DocumentBuilderFactory dbf=DocumentBuilderFactory.newInstance();
		//ͨ��DocumentBuilderFactory����ʵ���õ�һ��������
		DocumentBuilder dBuilder=dbf.newDocumentBuilder();
		//ָ����Ҫ������XML�ļ�
		Document document=dBuilder.parse("src/class.xml");
		//list(document);
		read(document);
		
	}
	//��ʾ��һ��ѧ������Ϣ
	//���ȡ������ֵ
	public static void read(Document doc){
		NodeList nl=doc.getElementsByTagName("ѧ��");
		//ȡ����һ��ѧ��
		Element stu=(Element) nl.item(0);
		System.out.println("ѧ��ѧ�ţ�"+stu.getAttribute("id"));
		Element name=(Element) stu.getElementsByTagName("����").item(0);
		System.out.println(name.getTextContent());
		}
	//������XML�ļ�
	public static void list(Node node){
		if(node.getNodeType()==node.ELEMENT_NODE)
		{
		System.out.println("�ڵ����ƣ�"+node.getNodeName());
		}
		//ȡ��node���ӽڵ�
		NodeList nodelist=node.getChildNodes();
		//���б���
		for(int i=0;i<nodelist.getLength();i++){
			//��ȥ��ʾ
			Node n=nodelist.item(i);
			list(n);
		}
	}

}
