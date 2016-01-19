newoption {
	trigger = "no_engine_project",
	description	= "Produce a separate project that will not have the engine files in the solution"
}

newoption {
	trigger	= "path_prefix",
	value = "path",
	description	= "The prefix for the path "
}

newoption {
	trigger	= "project_name",
	value = "name",
	description	= "The name for the project "
}

newoption {
	trigger	= "tests",
	value = "name",
	description	= "The test projects that should be created ",
	allowed = {
		  { "base",    "Base Test Project" },
		  { "utilities",  "Utilities Test Project" },
		  { "ai",  "AI Test Project" },
		  { "graphics",  "Graphics Test Project" },
		  { "physics",  "Physics Test Project" },
		  { "sound",  "Sound Test Project" },
		  { "gamebase",  "GameBase Test Project" }
	  }
}

newoption {
	trigger = "no_editor",
	description	= "Produce a separate project that will not have the engine files in the solution"
}
