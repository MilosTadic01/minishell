#ifndef AESTHETICS_H
# define AESTHETICS_H

# define NC		"\e[0m"
# define GRAY	"\e[30m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define GOLD	"\e[33m"
# define PINK   "\e[35m"
# define CYAN	"\e[36m"
# define GRB    "\e[90m"
# define REB    "\e[91m"
# define YEB    "\e[93m"
# define BLB    "\e[94m"
# define MAB    "\e[95m"
# define CYB    "\e[96m"
# define WHB    "\e[97m"

# define GREETING  NC \
",---.    ,---." PINK ".-./`)" NC " ,---.   .--." RED ".-./`)" NC "  " \
"  .-'''-. .---.  .---.     .-''-.    .---.     .---.      \n" \
"|    \\  /    |" PINK "\\ " GOLD ".-." PINK "')" NC \
"|    \\  |  |" RED "\\ " GOLD ".-." RED "') " NC \
" / " CYAN "_" NC "     \\|   |  |" GREEN "_ _" NC "|   .'" PINK \
"_ _ " NC "  \\   | " WHB ",_" NC "|     | " BLB ",_" NC "|      \n" \
"|  ,  \\/  ,  |" PINK "/ " GOLD "`-'" PINK " \\" NC "|  ,  \\ |  |" \
RED "/ " GOLD "`-' " \
RED "\\ " CYAN "(`' )" NC "/`--'|   |  " GREEN "( ' )" NC \
"  / " PINK "( ` )  " NC " '" WHB ",-./  )" \
BLB "   ,-./  )" NC "      \n" \
"|  |\\" BLB "_" NC "   /|  | " PINK "`-'`\"`" NC "|  |\\" \
GRB "_" NC " \\|  |" RED " `-'`\"`" CYAN \
"(_ " GOLD "o" CYAN " _)" NC ".   |   '-" GREEN "(_" GOLD "{;}" \
GREEN "_)" NC ". " PINK "(_ " GOLD "o" PINK " _)" NC "  |" WHB "\\  '" \
GOLD "_" WHB " '`)" BLB " \\  '" GOLD "_ " BLB "'`)  " NC "  \n" \
"|  " BLB "_( )_" NC "/ |  | .---. |  " GRB "_( )_" NC "\\  | .---.  " \
CYAN "(_,_)" NC ". '. |      " GREEN "(_,_) " NC "|  " PINK "(_,_)" \
NC "___| " WHB "> " GOLD "(_) " WHB " ) " BLB " > " GOLD "(_) " BLB " ) " \
NC "   \n" \
"| " BLB "(_ " GOLD "o" BLB " _) " NC "|  | |   | | " GRB "(_ " \
GOLD "o" GRB " _) " NC " | |   | " \
".---.  \\  :| " REB "_ _" NC "--.   | '  \\   .---." WHB "(  .  .-' " \
BLB "(  .  .-' " NC "   \n" \
"| " BLB " (_,_) " NC " |  | |   | | " GRB " (_,_)" NC "\\  | |   |" \
" \\    `-'  ||" REB "( ' )" NC " |   |  \\  `-'    / " WHB "`-'`-'" \
NC "|___" BLB "`-'`-'" NC "|___  \n" \
"|  |      |  | |   | |  |    |  | |   | " \
" \\       / " REB "(_" GOLD "{;}" REB "_)" \
NC "|   |   \\       /   |        \\|        \\ \n" \
"'--'      '--' '---' '--'    '--' '---' " \
"  `-...-'  '" REB "(_,_)" NC " '---'    `'-..-'    `--------``--------` \n" \
"By:\n" \
"Daria Zubkova <" CYAN "dzubkova@student.42.fr" NC ">\n" \
"Milos Tadic <" CYAN "mitadic@student.42.fr" NC ">\n"

#endif