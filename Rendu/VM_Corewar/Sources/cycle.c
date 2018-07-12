/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/03 11:38:10 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 13:09:17 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

static int			read_params(int cursor, t_op instruction, t_process **proc)
{
	int i;
	int param;

/* comment on sauvegarde le type des params ? car la on ecrit par dessus dans params[4] */
	param = 0;
	i = 0;
	while (instruction.params[i] || (!instruction.info_params && !param))
	{
		if (instruction.params[i] == 1)
			instruction = get_reg(cursor++, instruction, i);
		else if (instruction.params[i] == 2 || instruction.opcode == 1)
		{
			instruction = get_dir(cursor, instruction, i);
			cursor += (instruction.size_dir == 1 ? 2 : 4);
		}
		else if (instruction.params[i] == 3 || instruction.opcode == 9 ||
				instruction.opcode == 12 || instruction.opcode == 15)
		{
			instruction = get_ind(cursor, instruction, i);
			cursor += 2;
		}
		dprintf(1, "instruction.params[%d] = %d\n", i, instruction.params[i]);
		param++;
		i++;
	}
	(void)proc;
	/* ajouter l'instruction a la fetchqueue de *proc*/
	return (cursor);
}

static int			read_ocp(int cursor, t_op instruction, t_process **proc)
{
	unsigned char	ocp;
	int				i;

	i = 0;
	ocp = g_vm->map[cursor];
	instruction.params[0] = ocp >> 6 & 0x3;
	instruction.params[1] = ocp >> 4 & 0x3;
	instruction.params[2] = ocp >> 2 & 0x3;
	instruction.params[3] = ocp & 0x3;
	return (read_params(++cursor, instruction, proc));
}


static void				read_instruction(t_process *proc)
{
	t_op				instruction;
	int					cursor;

	dprintf(1, "PC = %d\n", proc->registers[0]);
	cursor = proc->registers[0];
	instruction = get_opcode(g_vm->map[cursor]);
	ft_printf("OPCODE = %d\n", g_vm->map[cursor]);
	ft_printf("instruction = %s\n", instruction.name);
	dprintf(1, "info params = %d\n", instruction.info_params);
	if (instruction.info_params)
		proc->registers[0] = read_ocp(++cursor, instruction, &proc);
	else
		proc->registers[0] = read_params(++cursor, instruction, &proc);
}
int		cycle_process()
{
	t_process	*proc;
	proc = g_vm->list_process;
	while (proc)
	{
		if (!proc->cycle_delay /*&& !proc->fetchqueue*/)
		{
			read_instruction(proc); //jump au prochain op puis read l'instruction + le bit d'encodage et on l'insere dans la fetchqueue
		}
		else if (!proc->cycle_delay && proc->fetchqueue)
		{
			//exec_process();
		}
		else
			proc->cycle_delay--;
		proc = proc->next;
	}
	return (0);
}

/*
void			*exec_process()
{

}
*/
