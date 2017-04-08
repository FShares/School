package com.dom;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class dom_traversal {
	public static void main(String[] args) throws Exception {
		// 创建一个DocumentBuilderFactory
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
		// 通过DocumentBuilderFactory 工厂实例得到一个解析器
		DocumentBuilder dBuilder = dbf.newDocumentBuilder();
		// 指定需要解析的XML文件
		Document document = dBuilder.parse("src/class.xml");
		//readXML(document);
		// list(document);
		// read(document);
		// add(document);
		// del(document);
		update(document);
	}
	//更新XML节点元素
	public static void update(Document doc) throws Exception{
		//要更新节点，先找到节点
		Element element = (Element) doc.getElementsByTagName("学生").item(0);
		Element element_name= (Element) element.getElementsByTagName("名字").item(0);
		element_name.setTextContent("李小龙");
		//更改属性
		element_name.setAttribute("sx", "lxl");//更新 ,源自add函数复制
		// 得到TransformerFactory
		TransformerFactory tff = TransformerFactory.newInstance();
		// 通过TransforemerFactory工厂得到一个转换器	
		Transformer tf = tff.newTransformer();	
		tf.transform(new DOMSource(doc), new StreamResult("src/class.xml"));

	}
	// 删除一个学生节点
	public static void del(Document doc) throws Exception {
		// 要删除，先要找到
//		Node node = doc.getElementsByTagName("学生").item(0);
//		node.getParentNode().removeChild(node);
		// 删除节点中的属性
		Node element = doc.getElementsByTagName("学生").item(0);
		element.getAttributes().removeNamedItem("id");
		//更新 ,源自add函数复制
		// 得到TransformerFactory
		TransformerFactory tff = TransformerFactory.newInstance();
		// 通过TransforemerFactory工厂得到一个转换器	
		Transformer tf = tff.newTransformer();	
		tf.transform(new DOMSource(doc), new StreamResult("src/class.xml"));
	}

	public static void add(Document doc) throws Exception {
		// 创建一个新的学校节点
		Element newstu = doc.createElement("学生");
		newstu.setAttribute("id", "a003");
		// 创建学生节点下面的子标签
		Element newstu_name = doc.createElement("名字");
		newstu_name.setTextContent("张张");
		Element newstu_age = doc.createElement("年龄");
		newstu_age.setTextContent("22");
		Element newstu_intro = doc.createElement("介绍");
		newstu_intro.setTextContent("小兵兵");
		// 把创建好的学生节点的子标签，回到newstu这个节点下面
		newstu.appendChild(newstu_name);
		newstu.appendChild(newstu_age);
		newstu.appendChild(newstu_intro);
		// 把新节点，添加到根元素下
		doc.getDocumentElement().appendChild(newstu);
		// 得到TransformerFactory
		TransformerFactory tff = TransformerFactory.newInstance();
		// 通过TransforemerFactory工厂得到一个转换器
		Transformer tf = tff.newTransformer();
		tf.transform(new DOMSource(doc), new StreamResult("src/class.xml"));
	}

	// 遍历XML文件
	public static void list(Node node) {
		if (node.getNodeType() == Node.ELEMENT_NODE) {
			System.out.println("Node name: " + node.getNodeName());
		}
		// 取出node的子节点
		NodeList nodelist = node.getChildNodes();
		// 进行遍历
		for (int i = 0; i < nodelist.getLength(); i++) {
			// 显示
			// System.out.println(nodelist.item(i));
			list(nodelist.item(i));
		}
	}

	// 显示xml中学生的信息
	public static void read(Document doc) {
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
				System.out.println("\n找到一名学生. 其ID: "
						+ node1.getAttributes().getNamedItem("id")
								.getNodeValue() + ". ");
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
