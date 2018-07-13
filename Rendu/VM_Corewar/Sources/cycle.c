/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/03 11:38:10 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 16:00:34 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

static int			read_params(int cursor, t_op instruction, t_process **proc)
{
	int i;
	int param;

	param = 0;
	i = 0;
	while (((*proc)->fetchqueue[i][0] || (!instruction.info_params && !param))
			&& i < 4)
	{
		if ((*proc)->fetchqueue[i][0] == 1)
			(*proc)->fetchqueue[i][1] = get_reg(cursor++);
		else if ((*proc)->fetchqueue[i][0] == 2 || instruction.opcode == 1)
		{
			(*proc)->fetchqueue[i][1] = get_dir(cursor, instruction);
			cursor += (instruction.size_dir == 1 ? 2 : 4);
		}
		else if ((*proc)->fetchqueue[i][0] == 3 || instruction.opcode == 9 ||
				instruction.opcode == 12 || instruction.opcode == 15)
		{
			(*proc)->fetchqueue[i][1] = (short)get_ind(cursor);
			cursor += 2;
		}
		param++;
		i++;
	}
	int j = 0;
	while (j < 4)
	{
		/*ft_printf("fetch[%d][0] = %d\n", j, (*proc)->fetchqueue[j][0]);
		ft_printf("fetch[%d][1] = %d\n", j, (*proc)->fetchqueue[j][1]);*/
		j++;
	}
	return (cursor);
}

static int			read_ocp(int cursor, t_op instruction, t_process **proc)
{
	unsigned char	ocp;

	ocp = g_vm->map[cursor];
	(*proc)->fetchqueue[0][0] = ocp >> 6 & 0x3;
	(*proc)->fetchqueue[1][0] = ocp >> 4 & 0x3;
	(*proc)->fetchqueue[2][0] = ocp >> 2 & 0x3;
	(*proc)->fetchqueue[3][0] = ocp & 0x3;
	return (read_params(++cursor, instruction, proc));
}

static void				read_instruction(t_process **proc)
{
	t_op				instruction;
	int					cursor;
	int				i;

	i = 0;
	while (i < 4)
	{
		(*proc)->fetchqueue[i][0] = 0;
		(*proc)->fetchqueue[i++][1] = -1;
	}
	cursor = (*proc)->registers[0];
	instruction = get_opcode(g_vm->map[cursor]);
//	dprintf(1, "PC = %d | Player : %d\n", (*proc)->registers[0], (*proc)->registers[1]);
//	ft_printf("OPCODE = %d\n", g_vm->map[cursor]);
//	ft_printf("instruction = %s\n", instruction.name);
//	dprintf(1, "info params = %d\n", instruction.info_params);
	if (instruction.info_params)
		(*proc)->registers[0] = read_ocp(++cursor, instruction, proc) % MEM_SIZE;
	else
		(*proc)->registers[0] = read_params(++cursor, instruction, proc) % MEM_SIZE;
}

int		cycle_process()
{
	t_process	*proc;

	proc = g_vm->list_process;
	while (proc)
	{
		if (proc->cycle_delay == -1)
		{
			read_instruction(&proc); //jump au prochain op puis read l'instruction + le bit d'encodage et on l'insere dans la fetchqueue
		}
		else if (!proc->cycle_delay)
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
