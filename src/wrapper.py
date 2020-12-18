# -*- coding: utf-8 -*-
callback=None
commander=0
moved=False
myteamId=0

import PyAI

from PyAI.interface import *
from PyAI import Team
from PyAI import BaseAI

import sys, traceback

aiClasses = {}	# {teamId:Class}
ais       = {}	# {teamId : ({event : function}, team)}
teams     = {}	# {teamId : team }


def handleEvent(teamId, topic, data):
	try:
		if topic == PyAI.EVENT_INIT:
			team = Team(teamId, data["callback"])
			teams[teamId] = team
			if teamId in aiClasses:
				ais[teamId]={}
				useTeam(teamId)
				aiClasses[teamId](team, {"ais":ais})

			else:
				return -1

		if teamId in ais and topic in ais[teamId]:
			useTeam(teamId)
			ais[teamId][topic](data)

	except:
		traceback.print_exception(sys.exc_type, sys.exc_value,sys.exc_traceback)


def useTeam(teamId):
	PyAI.team._currentTeam = teams[teamId]
