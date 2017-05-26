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
		//read(document);
		//add(document);
		//del(document);
		update(document);
		System.out.println("OK!");
		
	}
	//����XML�ڵ�Ԫ��
	public static void update(Document doc) throws Exception{
		//Ҫ���½ڵ㣬���ҵ��ڵ�
		Element element=(Element) doc.getElementsByTagName("ѧ��").item(0);
		Element element_name=(Element) element.getElementsByTagName("����").item(0);
		element_name.setTextContent("���¸�");
		//��������
		element_name.setAttribute("sx", "gdg");
		//���£���add����������
		//�õ�TransformerFactory
		TransformerFactory tff=TransformerFactory.newInstance();
		//ͨ��TransformerFactory�����õ�һ��ת����
		Transformer tf=tff.newTransformer();
		tf.transform(new DOMSource(doc), new StreamResult("src/class.xml"));
		
	}
	
	
	//ɾ��һ��ѧ���ڵ�
	public static void del(Document doc) throws Exception{
		//Ҫɾ������Ҫ�ҵ�
		//Node node=doc.getElementsByTagName("ѧ��").item(0);
		//node.getParentNode().removeChild(node);
		//�������ɾ�������ڵ㣬���ǽڵ��е�����
		Element element=(Element) doc.getElementsByTagName("ѧ��").item(0);
		element.removeAttribute("id");
		
		//���£���add����������
		//�õ�TransformerFactory
		TransformerFactory tff=TransformerFactory.newInstance();
		//ͨ��TransformerFactory�����õ�һ��ת����
		Transformer tf=tff.newTransformer();
		tf.transform(new DOMSource(doc), new StreamResult("src/class.xml"));
		
	}
	
	
	//����һ��ѧ����XML�ļ���
	public static void add(Document doc) throws Exception{
		//����һ���µ�ѧ���ڵ�
		Element newstu=doc.createElement("ѧ��");
		//���һ������ֵ
		newstu.setAttribute("id", "a003");
		//����ѧ���ڵ�������ӱ�ǩ
		Element newstu_name=doc.createElement("����");
		newstu_name.setTextContent("С��");
		Element newstu_age=doc.createElement("����");
		newstu_age.setTextContent("26");
		Element newstu_intro=doc.createElement("����");
		newstu_intro.setTextContent("С���Ÿ�");
		//�Ѵ����õ�ѧ���ڵ���ӱ�ǩ���ӵ�newstu����ڵ�����
		newstu.appendChild(newstu_name);
		newstu.appendChild(newstu_age);
		newstu.appendChild(newstu_intro);
		//���½ڵ㣬��ӵ���Ԫ����
		doc.getDocumentElement().appendChild(newstu);
		//�õ�TransformerFactory
		TransformerFactory tff=TransformerFactory.newInstance();
		//ͨ��TransformerFactory�����õ�һ��ת����
		Transformer tf=tff.newTransformer();
		tf.transform(new DOMSource(doc), new StreamResult("src/class.xml"));
		
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
