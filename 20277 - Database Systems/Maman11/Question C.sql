--Question C
--AlexZ

insert into customer
	values 
	('100','Anne','roses 202'),
	('101','Jacob','pine 3'),
	('104','Jack','park 25'),
	('107','Lily','fox 14'),
	('109','Kate','king 23'),
	('110','John','pine 15');


insert into magazine
	values 
	('Astronomy Today','1st Publisher','astronomy','month','www.astronomytoday.com'),
	('Bicycling','2nd Publisher','bicycling','week','www.bicycling.com'),
	('Bridal Guide','3rd Publisher','weddings','month','www.bridalguide.com'),
	('Health Magazine','1st Publisher','health','month','www.health.com'),
	('Cross Stitch magazine','2nd Publisher','sewing','month','www.just-crossstich.com'),
	('Click Magazine','3rd Publisher','kids,science','week','www.clickmagkids.com'),
	('Elle','1st Publisher','fashion','year','www.elle.com');



insert into pricing
	values 
	('Astronomy Today','1st Publisher','regular','6','45'),
	('Astronomy Today','1st Publisher','regular','12','43'),
	('Astronomy Today','1st Publisher','regular','24','41'),
	('Astronomy Today','1st Publisher','regular','36','41'),
	('Astronomy Today','1st Publisher','regular','60','41'),
	('Bicycling','2nd Publisher','regular','6','70'),
	('Bicycling','2nd Publisher','regular','12','73'),
	('Bicycling','2nd Publisher','regular','24','65'),
	('Bicycling','2nd Publisher','regular','36','65'),
	('Bicycling','2nd Publisher','regular','60','60'),	
	('Bridal Guide','3rd Publisher','regular','6','70'),
	('Bridal Guide','3rd Publisher','regular','12','65'),
	('Health Magazine','1st Publisher','regular','12','80'),
	('Health Magazine','1st Publisher','regular','24','75'),
	('Health Magazine','1st Publisher','regular','36','72'),
	('Click Magazine','3rd Publisher','regular','6','59'),
	('Click Magazine','3rd Publisher','regular','12','53'),
	('Click Magazine','3rd Publisher','regular','24','59');


insert into subscribes values
('100','Astronomy Today','1st Publisher','regular','6','4/4/2015'),
('101','Astronomy Today','1st Publisher','regular','6','10/23/2014'),
('100','Bridal Guide','3rd Publisher','regular','6','4/4/2015'),
('107','Bridal Guide','3rd Publisher','regular','6','4/29/2015'),
('101','Bridal Guide','3rd Publisher','regular','6','4/1/2014'),
('100','Click Magazine','3rd Publisher','regular','6','12/20/2014'),
('104','Click Magazine','3rd Publisher','regular','12','5/2/2014'),
('101','Health Magazine','1st Publisher','regular','12','5/3/2015'),
('104','Health Magazine','1st Publisher','regular','24','5/2/2014'),
('104','Bicycling','2nd Publisher','regular','6','10/23/2014'),
('110','Bicycling','2nd Publisher','regular','6','5/7/2015'),
('109','Bicycling','2nd Publisher','regular','60','5/1/2015'),
('100','Astronomy Today','1st Publisher','renew','6','4/22/2015'),
('100','Click Magazine','3rd Publisher','renew','24','5/2/2014'),
('109','Bicycling','2nd Publisher','renew','60','4/23/2015');

select * from customer ;




