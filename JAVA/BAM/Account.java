package BAM;

public class Account {
	private long id;
	private String pass;
	private String name;	//��ʵ���� 
	private String personID;//���֤�����ַ�������
	private String email;
	private double balance;
	
	private double deposit(double money){
		//����
		return money;
	}

	private double withdraw(double money){
		//ȡ���
		return money;
	}
	/*
	 * ���췽��: �вκ��޲�
	 * �вι��췽���������ñ�Ҫ������  
	 */
	Account(){
		this.id = 0;
		this.pass = "";
		this.name = "";
		this.personID = "";
		this.email = "";
		this.balance = 0;
	}
	Account(long id, String pass, String name, String personID, String email, long balance){

		this.id = id;
		this.pass = pass;
		this.name = name;
		this.personID = personID;
		this.email = email;
		this.balance = balance;
	}

	/*
	 * (��װ) ��Account��������ȫ��װ,ע��:Ҫ���ÿ�����Ե�set/get�����Ƿ���Ҫ����  
	 */
	public long getId() {
		return id;
	}

	private void setId(long id) {
		this.id = id;
	}

	public String getPass() {
		return pass;
	}

	private void setPass(String pass) {
		this.pass = pass;
	}

	public String getName() {
		return name;
	}

	private void setName(String name) {
		this.name = name;
	}

	public String getPersonID() {
		return personID;
	}

	private void setPersonID(String personID) {
		this.personID = personID;
	}

	public String getEmail() {
		return email;
	}

	private void setEmail(String email) {
		this.email = email;
	}

	public double getBalance() {
		return balance;
	}

	private void setBalance(double balance) {
		this.balance = balance;
	}
}
