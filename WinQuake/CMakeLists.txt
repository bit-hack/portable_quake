cmake_minimum_required(VERSION 3.0)
project(quake)

find_package(sdl REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

add_definitions(-D__WIN32__)

set(SOURCES
	adivtab.h
	anorm_dots.h
	anorms.h
	asm_draw.h
	asm_i386.h
	block16.h
	block8.h
	bspfile.h
#	cd_sdl.c
	cdaudio.h
	chase.c
	cl_demo.c
	cl_input.c
	cl_main.c
	cl_parse.c
	cl_tent.c
	clean.bat
	client.h
	cmd.c
	cmd.h
	common.c
	common.h
	conproc.h
	console.c
	console.h
	crc.c
	crc.h
	cvar.c
	cvar.h
#	d_copy.S
	d_edge.c
	d_fill.c
	d_iface.h
	d_ifacea.h
	d_init.c
	d_local.h
	d_modech.c
	d_part.c
	d_polyse.c
	d_scan.c
	d_sky.c
	d_sprite.c
	d_surf.c
	d_zpoint.c
#	dosasm.S
	dosisms.h
	draw.c
	draw.h
	host.c
	host_cmd.c
	input.h
	keys.c
	keys.h
	mathlib.c
	mathlib.h
	menu.c
	menu.h
	model.c
	model.h
	modelgen.h
	mpdosock.h
	net.h
#	net_bsd.c
#	net_bw.h
#	net_dgrm.c
#	net_dgrm.h
	net_loop.c
	net_loop.h
	net_main.c
#	net_udp.c
#	net_udp.h
#	net_vcr.c
#	net_vcr.h
#	net_wso.c
	pr_cmds.c
	pr_comp.h
	pr_edict.c
	pr_exec.c
	progdefs.h
	progs.h
	protocol.h
	quakeasm.h
	quakedef.h
	r_aclip.c
	r_alias.c
	r_bsp.c
	r_draw.c
	r_edge.c
	r_efrag.c
	r_light.c
	r_local.h
	r_main.c
	r_misc.c
	r_part.c
	r_shared.h
	r_sky.c
	r_sprite.c
	r_surf.c
	r_vars.c
#	r_varsa.S
	render.h
	resource.h
	sbar.c
	sbar.h
	screen.c
	screen.h
	server.h
#	snd_dma.c
#	snd_mem.c
#	snd_mix.c
#	snd_sdl.c
	sound.h
	spritegn.h
	sv_main.c
	sv_move.c
	sv_phys.c
	sv_user.c
	sys.h
	sys_sdl.c
	vgamodes.h
	vid.h
	vid_sdl.c
	view.c
	view.h
	wad.c
	wad.h
	winquake.h
	world.c
	world.h
	zone.c
	zone.h

    d_vars.c
	nonintel.c
    
    snd_null.c
    cd_null.c
    net_none.c
    )

add_executable(quake ${SOURCES})
target_link_libraries(quake ${SDL_LIBRARY})
