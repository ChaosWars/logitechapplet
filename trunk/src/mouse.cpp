/***************************************************************************
 *   Copyright (C) 2007 by Lawrence Lee   *
 *   valheru@facticius.net   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <linux/types.h>
#include <linux/hiddev.h>
#include "mouse.h"

#define LOGITECH	0x046d
#define MX_REVOLUTION	0xc51a	// version RR41.01_B0025
#define MX_REVOLUTION2	0xc525	// version RQR02.00_B0020

/*
 * The following code is based heavily on revoco.c written by Edgar Toernig <froese@gmx.de>
 * All credit for hacking the mice and discovering their commands go to him.
 */

 /*
 * Simple hack to control the wheel of Logitech's MX-Revolution mouse.
 *
 * Requires hiddev.
 *
 * Written November 2006 by E. Toernig's bonobo - no copyrights.
 *
 * Contact: Edgar Toernig <froese@gmx.de>
 *
 * Discovered commands:
 * (all numbers in hex, FS=free-spinning mode, CC=click-to-click mode):
 *   6 byte commands send with report ID 10:
 *   01 80 56 z1 00 00	immediate FS
 *   01 80 56 z2 00 00	immediate CC
 *   01 80 56 03 00 00	FS when wheel is moved
 *   01 80 56 04 00 00	CC when wheel is moved
 *   01 80 56 z5 xx yy	CC and switch to FS when wheel is rotated at given
 *			speed; xx = up-speed, yy = down-speed
 *			(speed in something like clicks per second, 1-50,
 *			 0 = previously set speed)
 *   01 80 56 06 00 00	?
 *   01 80 56 z7 xy 00	FS with button x, CC with button y.
 *   01 80 56 z8 0x 00	toggle FS/CC with button x; same result as 07 xx 00.
 *
 * If z=0 switch temporary, if z=8 set as default after powerup.
 *
 * Button numbers:
 *   0 previously set button
 *   1 left button	(can't be used for mode changes)
 *   2 right button	(can't be used for mode changes)
 *   3 middle (wheel) button
 *   4 rear thumb button
 *   5 front thumb button
 *   6 find button
 *   7 wheel left tilt
 *   8 wheel right tilt
 *   9 side wheel forward
 *  11 side wheel backward
 *  13 side wheel pressed
 */

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}


