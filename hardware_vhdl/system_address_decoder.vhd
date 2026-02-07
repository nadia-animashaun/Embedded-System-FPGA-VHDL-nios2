-- ------------------------------------------------------
-- system_address_decoder.vhd: customized logic for
--     enabling/selecting memory or I/O elements
--
-- Naraig Manjikian
-- September 2022
-- ------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

-- ------------------------------------------------------------------

entity system_address_decoder is
  port (
    addr_in    : in std_logic_vector(15 downto 4);
    rom_select : out std_logic;
    ram_select : out std_logic
  );
end entity;

-- ------------------------------------------------------------------

architecture rtl of system_address_decoder is

begin

rom_select <=   <logic expression inolving individual addr_in(..) bits> ;

ram_select <=   '1' when ( <vector comparison involving addr_in(..)> )
           else '0';

end architecture;
