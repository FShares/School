package com.dom;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class dom_traversal {
	public static void main(String[] args) throws Exception{
		//创建一个DocumentBuilderFactory
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
		//通过DocumentBuilderFactory 工厂实例得到一个解析器
		DocumentBuilder dBuilder = dbf.newDocumentBuilder();
		//指定需要解析的XML文件
		Document document = dBuilder.parse("src/class.xml");
		//list(document);
		//read(document);
		readXML(document);
	}
	//遍历XML文件
	public static void list(Node node){
		if(node.getNodeType()==Node.ELEMENT_NODE){
			System.out.println("Node name: "+node.getNodeName());
		}
		//取出node的子节点
		NodeList nodelist = node.getChildNodes();
		//进行遍历
		for(int i=0;i<nodelist.getLength();i++){
			//显示
			//System.out.println(nodelist.item(i));
			list(nodelist.item(i));
		}
	}
	//显示xml中学生的信息
	public static void read(Document doc){
		NodeList n1 = doc.getElementsByTagName("学生");
		Element stu = (Element) n1.item(0);
		Element name = (Element) stu.getElementsByTagName("名字").item(0);
		System.out.println(name.getTextContent());
	}
	
	 public static void readXML(Document doc) {
		 
		 // 得到一个elment根元素
		 Element element = doc.getDocumentElement();
		 // 获得根节点
		 System.out.println("根元素：" + element.getNodeName());

		   // 获得根元素下的子节点
		   NodeList childNodes = element.getChildNodes();

		   // 遍历这些子节点
		   for (int i = 0; i < childNodes.getLength(); i++) {
			   
			   // 获得每个对应位置i的结点
			   Node node1 = childNodes.item(i);
			   if ("学生".equals(node1.getNodeName())) {
			   // 如果节点的名称为"学生"，则输出Account元素属性type
				System.out.println("\n找到一名学生. 其ID: " + node1.getAttributes().getNamedItem("id").getNodeValue() + ". ");
			   }
			   // 获得<学生>下的节点
			     NodeList nodeDetail = node1.getChildNodes();
			     // 遍历<学生>下的节点
			     for (int j = 0; j < nodeDetail.getLength(); j++) {
			      // 获得<学生>元素每一个节点
			      Node detail = nodeDetail.item(j);
			      if ("名字".equals(detail.getNodeName())) // 输出code
			       System.out.println("名字: " + detail.getTextContent());
			      else if ("年龄".equals(detail.getNodeName())) // 输出pass
			       System.out.println("年龄: " + detail.getTextContent());
			      else if ("介绍".equals(detail.getNodeName())) // 输出name
			       System.out.println("介绍: " + detail.getTextContent());
			     }  
		   }
	 }
}
