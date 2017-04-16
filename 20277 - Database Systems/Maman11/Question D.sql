/*Question D
--AlexZ*/

create or replace function times (frequency varchar) returns float as $$
DECLARE times_sent float;
BEGIN
	case
	when frequency='day' then times_sent =(30/1);
	when frequency='week' then times_sent =(30/7);
	when frequency='biweek' then times_sent =(30/14);
	when frequency='month' then times_sent =(30/30);
	when frequency='bimonth' then times_sent =(30/60);
	when frequency='quarter' then times_sent =(30/91.25);
	when frequency='year' then times_sent =(30/365);
	when frequency='biyear' then times_sent =(30/730);
	end case;
	
return times_sent;
END;$$ language plpgsql;	

