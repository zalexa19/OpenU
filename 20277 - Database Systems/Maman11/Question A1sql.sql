--Question A
--Alex Zablotsky, 314494964

create table customer
	(cid numeric(5,0),
	name varchar(30),
	address varchar(50),
	primary key (cid));
	

create table magazine
	(title varchar(30),
	publisher varchar(30),
	topic varchar(30) not null,
	frequency varchar(10), 
	url varchar(100),
	primary key (title,publisher),
	check (frequency in ('day','week','biweek','month','bimonth','quarter','year','biyear')));


create table pricing
	(title varchar(30),
	publisher varchar(30),
	offer varchar(10),
	period integer,
	price numeric(3,0) not null,
	primary key (title,publisher,offer,period),
	foreign key(title,publisher) references magazine,
	check (period in ('6','12','24','36','60')));
	

create table subscribes 
	(cid numeric(5,0),
	title varchar(30),
	publisher varchar(30),
	offer varchar(10),
	period integer,
	sfrom date not null,
	foreign key (cid) references customer,
	foreign key (title,publisher,offer,period) references pricing);


