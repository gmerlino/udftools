/*
 * options.c
 *
 * Copyright (c) 2002       Ben Fennema <bfennema@falcon.csc.calpoly.edu>
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "cdrwtool.h"
#include "libudffs.h"
#include "defaults.h"
#include "options.h"

struct option long_options[] = {
	{ "help", no_argument, NULL, OPT_HELP },
	{ "device", 1, NULL, 'd' },
	{ "set write parameters", no_argument, NULL, 's' },
	{ "get write parameters", no_argument, NULL, 'g' },
	{ "blank cdrw disc", 1, NULL, 'b' },
	{ "format cdrw disc", 1,NULL, 'm' },
	{ "run mkudf on track", 1,NULL, 'u' },
	{ "set cd writing speed", 1, NULL, 't' },
	{ "write fixed packets", 1, NULL, 'p' },
	{ "perform quick setup", no_argument, NULL, 'q' },
	{ "reserve track", 1, NULL, 'r' },
	{ "close track", 1, NULL, 'c' },
	{ "fixed packet size", 1, NULL, 'z' },
	{ "border/session setting", 1, NULL, 'l' },
	{ "write type", 1, NULL, 'w' },
	{ "file to write", 2, NULL, 'f' },
	{ "start at this lba for file write", 1, NULL,'o' },
	{ "print detailed disc info", no_argument, NULL, 'i' },
	{ 0, 0, NULL, 0 },
};

void usage(void)
{
	int i;

	for (i = 0; long_options[i].name != NULL; i++)
		if (long_options[i].val >= 0xFF)
			printf("\t--%s\n", long_options[i].name);
		else
			printf("\t%c\t%s\n", long_options[i].val, long_options[i].name);
	exit(1);
}

void parse_args(int argc, char *argv[], struct cdrw_disc *disc, char *device)
{
	int retval;

	while ((retval = getopt_long(argc, argv, "r:t:im:u:d:sgqcb:p:z:l:w:f:o:h", long_options, NULL)) != EOF)
	{
		switch (retval)
		{
			case OPT_HELP:
			case 'h':
				usage();
				break;
			case 'c':
			{
				disc->close_track = 1;
				break;
			}
			case 'q':
			{
				disc->quick_setup = 1;
				break;
			}
			case 'u':
			{
				disc->mkudf = 1;
				disc->offset = strtol(optarg, NULL, 10);
				printf("mkudfing %lu blocks\n", disc->offset);
				break;
			}
			case 'r':
			{
				disc->reserve_track = strtol(optarg, NULL, 10);
				printf("reserving track %u\n", disc->reserve_track);
				break;
			}
			case 't':
			{
				disc->speed = strtol(optarg, NULL, 10);
				printf("setting speed to %d\n", disc->speed);
				break;
			}
			case 'm':
			{
				disc->format = 1;
				disc->offset = strtol(optarg, NULL, 10);
				printf("formatting %lu blocks\n", disc->offset);
				break;
			}
			case 'i':
			{
				disc->disc_track_info = 1;
				break;
			}
			case 'd':
			{
				strcpy(device, optarg);
				printf("using device %s\n", device);
				break;
			}
			case 'g':
			{
				printf("ok, want to get\n");
				disc->get_settings = 1;
				break;
			}
			case 's':
			{
				printf("ok, want to set\n");
				disc->set_settings = 1;
				break;
			}
			case 'b':
			{
				if (!strcmp("full", optarg))
				{
					printf("full blank\n");
					disc->blank = BLANK_FULL;
				}
				else if (!strcmp("fast", optarg))
				{
					printf("fast blank\n");
					disc->blank = BLANK_FAST;
				}
				else
				{
					printf("full or fast blanking only\n");
					exit(1);
				}
				break;
			}
			case 'p':
			{
				disc->fpacket = !!strtol(optarg, NULL, 10);
				printf("%s packets\n", disc->fpacket?"fixed":"variable");
				break;
			}
			case 'z':
			{
				disc->packet_size = strtol(optarg, NULL, 10);
				printf("packet size: %d\n", disc->packet_size);
				break;
			}
			case 'l':
			{
				disc->border = strtol(optarg, NULL, 10);
				printf("border type: %d\n", disc->border);
				break;
			}
			case 'w':
			{
				if (!strcmp("mode1", optarg))
				{
					printf("mode1\n");
					disc->write_type = 1;
				}
				else if (!strcmp("mode2", optarg))
				{
					printf("mode2\n");
					disc->write_type = 2;
				}
				else
				{
					fprintf(stderr, "mode1 or mode2 writing only\n");
					exit(1);
				}
				break;
			}
			case 'f':
			{
				strcpy(disc->filename, optarg);
				printf("write file %s\n", disc->filename);
				break;
			}
			case 'o':
			{
				disc->offset = strtoul(optarg, NULL, 10);
				printf("write offset %lu\n", disc->offset);
			}
		}
	}

	if (optind < argc)
		usage();
}
