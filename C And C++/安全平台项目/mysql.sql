


-- 创建 网点信息表 --编号 名称 描述 授权码 状态(0可用  1不可用)
CREATE TABLE SECNODE(
	id     				char(4) PRIMARY KEY, 
	name     			VARCHAR(128) NOT NULL,
 	nodedesc      		VARCHAR(512),
 	createtime			datetime,	
 	authcode			int(12),
 	state     			int(4)
);

INSERT INTO secnode VALUES('0001', '网银中心', '北京金融街23号', '15-7月-15', 1, 0);
INSERT INTO secnode VALUES('1111', '广东分中心1111', '广州天河金融', '15-7月-15', 1111, 0);
commit;

-- 创建 网点密钥表, 客户端网点 服务器端网点 密钥号 密钥产生时间 密钥状态 
CREATE TABLE SECKYEINFO(
	clientid          	char(4) constraint secmng_seckeynode_clientid_fk references SECNODE(id),
	serverid          	char(4) constraint secmng_seckeynode_serverid_fk references SECNODE(id),
	keyid            	int(9) PRIMARY KEY, 
	createtime			datetime,
	state				int(4),
	seckey				VARCHAR(512)
);

--创建索引 在新的表空间上
--CREATE  INDEX SECMNG.IX_SECKYEINFO_clientid ON SECMNG.SECKYEINFO(clientid) TABLESPACE ts_seckey_admin;
commit;



CREATE TABLE SRVCFG(
	key				VARCHAR(64),
	valude			VARCHAR(128)
);
	
-- 创建 交易信息表 交易者 交易时间 交易事件 交易描述 （什么人 在什么时间 干了什么事）
CREATE TABLE TRAN(
	iID					int(12) PRIMARY KEY,
 	tran_operator     	int,
 	trantime			datetime,
 	tranid          	int(4),
 	trandesc      		VARCHAR(512)	
);

commit;

    
