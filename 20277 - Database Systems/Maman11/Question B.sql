--Question B - Alex Zablotsky 314494964

create or replace function offer_f() returns trigger as $$
begin
	
	if  new.offer='regular' then		
		if  (tg_op)='INSERT' then
		insert into pricing 
		values(new.title,new.publisher,'renew',new.period,new.price*0.9);
		end if;
		
		if (tg_op='UPDATE') then
		update  pricing set price = new.price * 0.9 where
		title=new.title and publisher = new.publisher and period=new.period and offer ='renew'; 
		end if;
	end if;

return new;

end; 
$$ language plpgsql;	


create trigger reducecd_offer 
after insert or update on pricing
for each row
execute procedure offer_f();

