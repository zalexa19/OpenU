--Question E
--AlexZ

--E1
select m.title, m.publisher, m. frequency, m.url from pricing p natural join magazine m where p.period = '36';

--E2
select c.cid , c.name, count (cid) as subs from customer c natural join subscribes s
where s.title in (select  title as subs from  subscribes 
			group by title having (count (cid)>1))
group by c.cid
having (count (s.cid)=1);

--E3
select c.cid , c.name, count (cid) as subs from customer c natural join subscribes s
where cid not in (select distinct (cid) from subscribes where offer = 'renew')
group by c.cid having (count (cid) >2);

--E4---
with issues (title,publisher,offer,period,perissue) as 
(select p.title, p.publisher, p.offer,p.period, p.price/times(m.frequency) from pricing p natural join magazine m)

select p.title,p.publisher, p.offer, p.period , i.perissue from pricing p natural join issues i 
where i.perissue = (select max(i.perissue) from issues i);


--E5

with total_sum (cid,sumprice) as
	(select cid, sum(p.price) as sum from pricing p natural join subscribes 
	where sfrom + (30 * period) >= current_date
	group by cid)

select u.cid, u.name, t.sumprice from total_sum t natural join customer u
where sumprice = (select max (sumprice) from total_sum);

--E6

select p.title, p.publisher, p.period, p.price
	from pricing p , pricing t 
	where p.title=t.title and p.publisher=t.publisher and p.offer=t.offer and t.offer = 'regular' 
		and p.period < t.period and p.price <t.price ;

--E7
with all_topics (topic) as (select distinct topic from magazine)

select cid,count(cid) from (
	select cid, topic from customer
	natural join subscribes
	natural join magazine
	group by cid,topic) topic_count

group by cid
having count(cid) = (select count(*) from all_topics)

