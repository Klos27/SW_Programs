library ieee ;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity SystemHEX is
port( writedata: in std_logic_vector(31 downto 0);
		readdata: in std_logic_vector(31 downto 0);
      clk_clk, reset_reset_n:   in std_logic;
      wr, rd, cs : in std_logic;
		LED2: out std_logic_vector(1 downto 0);	-- led[0] = led1 , led[1] = led9 error
		HEX2: out std_logic_vector(6 downto 0));
end SystemHEX;
 
architecture rtl of SystemHEX is
signal reg: std_logic_vector(4 downto 0); 
signal ilosob: integer;    
begin

process(clk_clk)
begin
   if (clk_clk'event and clk_clk='1') then
      if(wr='1' and cs='1') then
        reg <=writedata(4 downto 0);
		 -- ilosob <= to_integer(signed(reg));
        end if;
    end if;
end process;

process(clk_clk)
begin
   if (clk_clk'event and clk_clk='1') then
		CASE reg IS
			WHEN "00000" => HEX2 <= "1000000";	--0
			WHEN "00001" => HEX2 <= "1111001";	--1
			WHEN "00010" => HEX2 <= "0100100";	--2
			WHEN "00011" => HEX2 <= "0110000";	--3
			WHEN "00100" => HEX2 <= "0011001";	--4
			WHEN "00101" => HEX2 <= "0010010";	--5
			WHEN "00110" => HEX2 <= "0000010";	--6
			WHEN "00111" => HEX2 <= "1111000";	--7
			WHEN "01000" => HEX2 <= "0000000";	--8
			WHEN "01001" => HEX2 <= "0010000";	--9
			WHEN "01010" => HEX2 <= "0111111";	-- - powyzej 9osob
			WHEN OTHERS => HEX2 <= "0000110";	--E
		END CASE;
	 	  
		if (reg="00000") then LED2 <= "00"; 			--led2
      elsif (reg = "00001" or reg = "00010" or reg = "00011" or reg = "00100" or reg = "00101" or reg = "00110"  or reg = "00111"  or reg = "01000"  or reg = "01001"  or reg = "01010") then LED2 <= "01"; --led2
		elsif (reg = "10001" or reg = "10010" or reg = "10011" or reg = "10100" or reg = "10101" or reg = "10110"  or reg = "10111"  or reg = "11000"  or reg = "11001"  or reg = "11010") then LED2 <= "11"; --led2 + error
		else
		LED2 <= "10"; -- error		
      end if;
    end if;
end process;

end rtl;