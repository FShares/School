package com.nz;

import javax.xml.parsers.*;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

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
		//read(document);
		//add(document);
		//del(document);
		update(document);
		System.out.println("OK!");
		
	}
	//更新XML节点元素
	public static void update(Document doc) throws Exception{
		//要更新节点，先找到节点
		Element element=(Element) doc.getElementsByTagName("学生").item(0);
		Element element_name=(Element) element.getElementsByTagName("名字").item(0);
		element_name.setTextContent("郭德纲");
		//更改属性
		element_name.setAttribute("sx", "gdg");
		//更新，从add函数处复制
		//得到TransformerFactory
		TransformerFactory tff=TransformerFactory.newInstance();
		//通过TransformerFactory工厂得到一个转换器
		Transformer tf=tff.newTransformer();
		tf.transform(new DOMSource(doc), new StreamResult("src/class.xml"));
		
	}
	
	
	//删除一个学生节点
	public static void del(Document doc) throws Exception{
		//要删除，先要找到
		//Node node=doc.getElementsByTagName("学生").item(0);
		//node.getParentNode().removeChild(node);
		//如果不是删除整个节点，而是节点中的属性
		Element element=(Element) doc.getElementsByTagName("学生").item(0);
		element.removeAttribute("id");
		
		//更新，从add函数处复制
		//得到TransformerFactory
		TransformerFactory tff=TransformerFactory.newInstance();
		//通过TransformerFactory工厂得到一个转换器
		Transformer tf=tff.newTransformer();
		tf.transform(new DOMSource(doc), new StreamResult("src/class.xml"));
		
	}
	
	
	//增加一个学生到XML文件中
	public static void add(Document doc) throws Exception{
		//创建一个新的学生节点
		Element newstu=doc.createElement("学生");
		//添加一个属性值
		newstu.setAttribute("id", "a003");
		//创建学生节点下面的子标签
		Element newstu_name=doc.createElement("名字");
		newstu_name.setTextContent("小张");
		Element newstu_age=doc.createElement("年龄");
		newstu_age.setTextContent("26");
		Element newstu_intro=doc.createElement("介绍");
		newstu_intro.setTextContent("小兵张嘎");
		//把创建好的学生节点的子标签，加到newstu这个节点下面
		newstu.appendChild(newstu_name);
		newstu.appendChild(newstu_age);
		newstu.appendChild(newstu_intro);
		//把新节点，添加到根元素下
		doc.getDocumentElement().appendChild(newstu);
		//得到TransformerFactory
		TransformerFactory tff=TransformerFactory.newInstance();
		//通过TransformerFactory工厂得到一个转换器
		Transformer tf=tff.newTransformer();
		tf.transform(new DOMSource(doc), new StreamResult("src/class.xml"));
		
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
