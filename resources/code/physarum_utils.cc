#include "physarum.h"
// This contains the lower level code

void physarum::create_window () {
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) {
		printf( "Error: %s\n", SDL_GetError() );
	}

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
	SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 8 );

	// this is how you query the screen resolution
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode( 0, &dm );

	// pulling these out because I'm going to try to span the whole screen with
	// the window, in a way that's flexible on different resolution screens
	int total_screen_width = dm.w;
	int total_screen_height = dm.h;

	cout << "creating window...";

	// window = SDL_CreateWindow( "OpenGL Window", 0, 0, total_screen_width, total_screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS );
	window = SDL_CreateWindow( "OpenGL Window", 0, 0, total_screen_width, total_screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE );
	SDL_ShowWindow( window );

	cout << "done." << endl;


	cout << "setting up OpenGL context...";
	// OpenGL 4.3 + GLSL version 430
	const char* glsl_version = "#version 430";
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, 0 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	GLcontext = SDL_GL_CreateContext( window );

	SDL_GL_MakeCurrent( window, GLcontext );
	SDL_GL_SetSwapInterval( 1 ); // Enable vsync
	// SDL_GL_SetSwapInterval(0); // explicitly disable vsync

	// CONTINUUM REPRESENTATION POINTS

	if ( glewInit() != GLEW_OK ) {
		fprintf( stderr, "Failed to initialize OpenGL loader!\n");
	}

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_POINT_SMOOTH );

	glPointSize( 3.0f );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); ( void )io; // void cast prevents unused variable warning

	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL( window, GLcontext );
	ImGui_ImplOpenGL3_Init( glsl_version );

	clear_color = ImVec4( 75.0f / 255.0f, 75.0f / 255.0f, 75.0f / 255.0f, 0.5f ); // initial value for clear color

	// really excited by the fact imgui has an hsv picker to set this
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear( GL_COLOR_BUFFER_BIT );
	SDL_GL_SwapWindow( window );

	cout << "done." << endl;
	ImVec4* colors = ImGui::GetStyle().Colors;

	colors[ ImGuiCol_Text ]                   = ImVec4( 0.64f, 0.37f, 0.37f, 1.00f );
	colors[ ImGuiCol_TextDisabled ]           = ImVec4( 0.49f, 0.26f, 0.26f, 1.00f );
	colors[ ImGuiCol_WindowBg ]               = ImVec4( 0.17f, 0.00f, 0.00f, 0.94f );
	colors[ ImGuiCol_ChildBg ]                = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	colors[ ImGuiCol_PopupBg ]                = ImVec4( 0.18f, 0.00f, 0.00f, 0.94f );
	colors[ ImGuiCol_Border ]                 = ImVec4( 0.35f, 0.00f, 0.03f, 0.50f );
	colors[ ImGuiCol_BorderShadow ]           = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	colors[ ImGuiCol_FrameBg ]                = ImVec4( 0.14f, 0.04f, 0.00f, 1.00f );
	colors[ ImGuiCol_FrameBgHovered ]         = ImVec4( 0.14f, 0.04f, 0.00f, 1.00f );
	colors[ ImGuiCol_FrameBgActive ]          = ImVec4( 0.14f, 0.04f, 0.00f, 1.00f );
	colors[ ImGuiCol_TitleBg ]                = ImVec4( 0.14f, 0.04f, 0.00f, 1.00f );
	colors[ ImGuiCol_TitleBgActive ]          = ImVec4( 0.14f, 0.04f, 0.00f, 1.00f );
	colors[ ImGuiCol_TitleBgCollapsed ]       = ImVec4( 0.00f, 0.00f, 0.00f, 0.51f );
	colors[ ImGuiCol_MenuBarBg ]              = ImVec4( 0.14f, 0.14f, 0.14f, 1.00f );
	colors[ ImGuiCol_ScrollbarBg ]            = ImVec4( 0.02f, 0.02f, 0.02f, 0.53f );
	colors[ ImGuiCol_ScrollbarGrab ]          = ImVec4( 0.31f, 0.31f, 0.31f, 1.00f );
	colors[ ImGuiCol_ScrollbarGrabHovered ]   = ImVec4( 0.41f, 0.41f, 0.41f, 1.00f );
	colors[ ImGuiCol_ScrollbarGrabActive ]    = ImVec4( 0.51f, 0.51f, 0.51f, 1.00f );
	colors[ ImGuiCol_CheckMark ]              = ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_SliderGrab ]             = ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_SliderGrabActive ]       = ImVec4( 1.00f, 0.33f, 0.00f, 1.00f );
	colors[ ImGuiCol_Button ]                 = ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_ButtonHovered ]          = ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_ButtonActive ]           = ImVec4( 1.00f, 0.33f, 0.00f, 1.00f );
	colors[ ImGuiCol_Header ]                 = ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_HeaderHovered ]          = ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_HeaderActive ]           = ImVec4( 1.00f, 0.33f, 0.00f, 1.00f );
	colors[ ImGuiCol_Separator ]              = ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_SeparatorHovered ]       = ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_SeparatorActive ]        = ImVec4( 1.00f, 0.33f, 0.00f, 1.00f );
	colors[ ImGuiCol_ResizeGrip ]             = ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_ResizeGripHovered ]      = ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_ResizeGripActive ]       = ImVec4( 1.00f, 0.33f, 0.00f, 1.00f );
	colors[ ImGuiCol_Tab ]                    = ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_TabHovered ]             = ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_TabActive ]              = ImVec4( 1.00f, 0.33f, 0.00f, 1.00f );
	colors[ ImGuiCol_TabUnfocused ]           = ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_TabUnfocusedActive ]     = ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_PlotLines ]              = ImVec4( 0.61f, 0.61f, 0.61f, 1.00f );
	colors[ ImGuiCol_PlotLinesHovered ]       = ImVec4( 1.00f, 0.43f, 0.35f, 1.00f );
	colors[ ImGuiCol_PlotHistogram ]          = ImVec4( 0.90f, 0.70f, 0.00f, 1.00f );
	colors[ ImGuiCol_PlotHistogramHovered ]   = ImVec4( 1.00f, 0.60f, 0.00f, 1.00f );
	colors[ ImGuiCol_TextSelectedBg ]         = ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_DragDropTarget ]         = ImVec4( 1.00f, 1.00f, 0.00f, 0.90f );
	colors[ ImGuiCol_NavHighlight ]           = ImVec4( 1.00f, 0.60f, 0.00f, 1.00f );
	colors[ ImGuiCol_NavWindowingHighlight ]  = ImVec4( 1.00f, 1.00f, 1.00f, 0.70f );
	colors[ ImGuiCol_NavWindowingDimBg ]      = ImVec4( 0.80f, 0.80f, 0.80f, 0.20f );
	colors[ ImGuiCol_ModalWindowDimBg ]       = ImVec4( 0.80f, 0.80f, 0.80f, 0.35f );
}

void physarum::gl_setup () {
	// some info on your current platform
	const GLubyte *renderer = glGetString( GL_RENDERER ); // get renderer string
	const GLubyte *version = glGetString( GL_VERSION );		// version as a string
	printf( "Renderer: %s\n", renderer );
	printf( "OpenGL version supported %s\n\n\n", version );

	// create the shader for the points to draw the physarum agents, which also does the movement logic
	agent_shader = Shader( "resources/code/shaders/agent.vs.glsl", "resources/code/shaders/agent.fs.glsl" ).Program;

	// create the shader for the triangles to draw the pheremone field
	continuum_shader = Shader( "resources/code/shaders/continuum.vs.glsl", "resources/code/shaders/continuum.fs.glsl" ).Program;

	// set up the points for the continuum
	//  A---------------B
	//  |          .    |
	//  |       .       |
	//  |    .          |
	//  |               |
	//  C---------------D

	// diagonal runs from C to B
	//  A is -1, 1
	//  B is  1, 1
	//  C is -1,-1
	//  D is  1,-1
	std::vector< glm::vec3 > points;

	points.clear();
	points.push_back( glm::vec3(-1.0f, 1.0f, 0.5f ) );  //A
	points.push_back( glm::vec3(-1.0f,-1.0f, 0.5f ) );  //C
	points.push_back( glm::vec3( 1.0f, 1.0f, 0.5f ) );  //B
	points.push_back( glm::vec3( 1.0f, 1.0f, 0.5f ) );  //B
	points.push_back( glm::vec3(-1.0f,-1.0f, 0.5f ) );  //C
	points.push_back( glm::vec3( 1.0f,-1.0f, 0.5f ) );  //D

	// vao, vbo
	cout << "  setting up vao, vbo for continuum model...";
	glGenVertexArrays( 1, &continuum_vao );
	glBindVertexArray( continuum_vao );

	glGenBuffers( 1, &continuum_vbo );
	glBindBuffer( GL_ARRAY_BUFFER, continuum_vbo );
	cout << "done." << endl;

	// buffer the data
	cout << "  buffering vertex data...";
	glBufferData(GL_ARRAY_BUFFER, sizeof( glm::vec3 ) * points.size(), NULL, GL_DYNAMIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( glm::vec3 ) * points.size(), &points[ 0 ] );
	cout << "done." << endl;

	// set up attributes
	cout << "  setting up attributes in continuum shader...";
	GLuint points_attrib = glGetAttribLocation( continuum_shader, "vPosition" );
	glEnableVertexAttribArray( points_attrib );
	glVertexAttribPointer( points_attrib, 3, GL_FLOAT, GL_FALSE, 0, ( GLvoid* ) ( static_cast<const char*>( 0 ) + ( 0 ) ) );
	cout << "done." << endl;

	// create the compute shader for the diffusion and decay of the pheremone field
	diffuse_and_decay_shader = CShader( "resources/code/shaders/diffuse_and_decay.cs.glsl" ).Program;

	// create the image2d object for the pheremone field
	// 16-bit, one channel image texture with GL_R16UI or maybe 32 bit with GL_R32UI
	// seed with all zero values or some data generated with std::random

	std::vector< unsigned int > data;
	PerlinNoise p;
	for ( unsigned int x = 0; x < 2048; x++ )
		for ( unsigned int y = 0; y < 2048; y++ )
			data.push_back( ( 1 << 18 ) * p.noise( 0.01f * x, 0.01f * y, 0.3f ) );

	glGenTextures( 2, &continuum_textures[ 0 ] );
	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, continuum_textures[ 0 ]); // use the specified ID
	glTexImage2D( GL_TEXTURE_2D, 0, GL_R32UI, DIM, DIM, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, &data[ 0 ] ); //pass non-null to initialize with some pheremone pattern
	glBindImageTexture( 1, continuum_textures[ 0 ], 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32UI );

	glActiveTexture( GL_TEXTURE2 );
	glBindTexture( GL_TEXTURE_2D, continuum_textures[ 1 ] );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_R32UI, DIM, DIM, 0,  GL_RED_INTEGER, GL_UNSIGNED_INT, NULL );
	glBindImageTexture( 2, continuum_textures[ 1 ], 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32UI );

	// create the SSBO for the agent positions, directions
	// only needs to be set up for the agent shader
	std::vector<GLfloat> agent_data;
	long unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine engine{ seed };
	std::uniform_real_distribution<GLfloat> udistribution{ -1.0f, 1.0f };
	std::normal_distribution<GLfloat> ndistribution( 0.0f, 0.3f );

	udistribution.reset();
	ndistribution.reset();

	for ( int i = 0; i <= NUM_AGENTS; i++ ) {
		glm::vec2 pos, dir;

		if ( !true ) {
			pos.x = ndistribution( engine );
			pos.y = ndistribution( engine );
		} else {
			pos.x = udistribution( engine );
			pos.y = udistribution( engine );
		}

		dir.x = udistribution( engine );
		dir.y = udistribution( engine );
		dir = glm::normalize( dir );  //we want unit length
		agent_data.push_back( static_cast< GLfloat >( pos.x ) );
		agent_data.push_back( static_cast< GLfloat >( pos.y ) );
		agent_data.push_back( static_cast< GLfloat >( dir.x ) );
		agent_data.push_back( static_cast< GLfloat >( dir.y ) );
	}

	glGenBuffers( 1, &agent_ssbo );
	glBindBuffer( GL_SHADER_STORAGE_BUFFER, agent_ssbo );	// v I had left out a factor of two here, I had never solved this bug but it's super simple
	glBufferData( GL_SHADER_STORAGE_BUFFER, sizeof( GLfloat ) * 2 * 2 * NUM_AGENTS, ( GLvoid * ) &agent_data[ 0 ], GL_DYNAMIC_COPY );
	glBindBufferBase( GL_SHADER_STORAGE_BUFFER, 0, agent_ssbo );

	sense_angle = 2.4540f;
	sense_distance = 0.0013f;
	turn_angle = 1.250f;
	step_size = 0.0006f;
	deposit_amount = 1250;
	decay_factor = 0.9875f;
}


void physarum::sim_tick () {
	// run the diffuse_and_decay_shader
	glUseProgram( diffuse_and_decay_shader );

	//swap the images
	std::swap( continuum_textures[ 0 ], continuum_textures[ 1 ] );
	glBindImageTexture( 1, continuum_textures[ 0 ], 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32UI );
	glBindImageTexture( 2, continuum_textures[ 1 ], 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32UI );
	glUniform1f( glGetUniformLocation( diffuse_and_decay_shader, "decay_factor" ), decay_factor );

	glDispatchCompute( DIM / 8, DIM / 8, 1 );
	glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
}


static void HelpMarker ( const char* desc ) {
	ImGui::TextDisabled( "(?)" );
	if ( ImGui::IsItemHovered() )	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos( ImGui::GetFontSize() * 35.0f );
		ImGui::TextUnformatted( desc );
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void physarum::draw_everything () {
	ImGuiIO& io = ImGui::GetIO(); ( void )io; // void cast prevents unused variable warning

	glClearColor( clear_color.x, clear_color.y, clear_color.z, clear_color.w );   // from hsv picker
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );                     // clear the background

	static float agent_pointsize = 3.0f;
	static bool show_trails = true;
	static bool show_agents = false;
	static ImU32 deposit_amt = deposit_amount;

	// draw the stuff on the GPU
	// continuum
	glUseProgram( continuum_shader );
	glBindVertexArray( continuum_vao );
	glBindBuffer( GL_ARRAY_BUFFER, continuum_vbo );
	glUniform1i( glGetUniformLocation( continuum_shader, "show_trails" ), show_trails );
	glDrawArrays( GL_TRIANGLES, 0, 6 );

	// agents
	glUseProgram( agent_shader );
	glPointSize( agent_pointsize );

	// generation of the random values to be used in the shader
	std::vector< glm::vec2 > random_directions;
	long unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::default_random_engine gen{ seed };
	std::uniform_real_distribution< GLfloat > dist{ -1.0f, 1.0f };

	for ( int i = 0; i < 8; i++ )
		random_directions.push_back( glm::normalize( glm::vec2( dist( gen ), dist( gen ) ) ) );

	glUniform2fv( glGetUniformLocation( agent_shader, "random_values" ), 8, glm::value_ptr( random_directions[ 0 ] ) );

	// the rest of the simulation parameters
	glUniform1i( glGetUniformLocation( agent_shader, "show_agents" ), show_agents );
	glUniform1f( glGetUniformLocation( agent_shader, "step_size" ), step_size );
	glUniform1f( glGetUniformLocation( agent_shader, "sense_angle" ), sense_angle );
	glUniform1f( glGetUniformLocation( agent_shader, "sense_distance" ), sense_distance );
	glUniform1f( glGetUniformLocation( agent_shader, "turn_angle" ), turn_angle );
	glUniform1ui( glGetUniformLocation( agent_shader, "deposit_amount" ), deposit_amount );

	glDrawArrays( GL_POINTS, 0, NUM_AGENTS/2 );

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame( window );
	ImGui::NewFrame();

	// do my own window
	ImGui::SetNextWindowPos( ImVec2( 10, 10 ) );
	ImGui::SetNextWindowSize( ImVec2( 256, 410 ) );
	ImGui::Begin( "Controls", NULL, 0 );

	if ( ImGui::SmallButton( "Randomize Parameters" ) ) {
		long unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine engine{ seed };
		std::uniform_real_distribution<GLfloat> senseAngleDistribution( 0.0f, float( pi ) );
		std::uniform_real_distribution<GLfloat> senseDistanceDistribution( 0.0f, 0.005f );
		std::uniform_real_distribution<GLfloat> turnAngleDistribution( 0.0f, float( pi ) );
		std::uniform_real_distribution<GLfloat> stepSizeDistribution( 0.0f, 0.005f );
		std::uniform_int_distribution<int> depositAmountDistribution( 4000, 75000 );
		std::uniform_real_distribution<GLfloat> decayFactorDistribution( 0.75f, 1.0f );

		// generate new values based on above distributions
		sense_angle = senseAngleDistribution( engine );
		sense_distance = senseDistanceDistribution( engine );
		turn_angle = turnAngleDistribution( engine );
		step_size = stepSizeDistribution( engine );
		deposit_amount = depositAmountDistribution( engine );
		decay_factor = decayFactorDistribution( engine );
	}


	// widgets
	ImGui::Text("Sensor Angle:                ");
	ImGui::SameLine();
	HelpMarker("The angle between the sensors.");
	ImGui::SliderFloat("radians", &sense_angle, 0.0f, 3.14f, "%.4f");

	ImGui::Separator();

	ImGui::Text("Sensor Distance:             ");
	ImGui::SameLine();
	HelpMarker("The distance from the agent position to the sensors.");
	ImGui::SliderFloat("        ", &sense_distance, 0.0f, 0.005f, "%.4f");

	ImGui::Separator();

	ImGui::Text("Turn Angle:                  ");
	ImGui::SameLine();
	HelpMarker("Amount that each simulation agent can turn in the movement shader.");
	ImGui::SliderFloat("radians ", &turn_angle, 0.0f, 3.14f, "%.4f");

	ImGui::Separator();

	ImGui::Text("Step Size:                   ");
	ImGui::SameLine();
	HelpMarker("Distance that each sim agent will go in their current direction each step.");
	ImGui::SliderFloat("    ", &step_size, 0.0f, 0.005f, "%.4f");

	ImGui::Separator();

	ImGui::Text("Deposit Amount:              ");
	deposit_amt = deposit_amount;
	ImGui::SameLine();
	HelpMarker("Amout of pheremone that is deposited by each simulation agent.");
	ImGui::DragScalar("  ", ImGuiDataType_U32, &deposit_amt, 50, NULL, NULL, "%u units");

	//update the deposit amount
	if( deposit_amt != deposit_amount )
		deposit_amount = static_cast<GLuint>(deposit_amt);

	ImGui::Separator();

	ImGui::Text("Decay Factor:                ");
	ImGui::SameLine();
	HelpMarker("Scale factor applied when storing the result of the gaussian blur.");
	ImGui::SliderFloat("              ", &decay_factor, 0.75f, 1.0f, "%.4f");

	ImGui::Separator();
	ImGui::Separator();

	ImGui::Text("Agent Pointsize:             ");
	ImGui::SameLine();
	HelpMarker("Size of the points used to render the simulation agents.");
	ImGui::SliderFloat(" ", &agent_pointsize, 0.75f, 10.0f, "%.3f");

	ImGui::Checkbox("Show Trails", &show_trails);
	ImGui::Checkbox("Show Agents", &show_agents);

	ImGui::End();
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );   // put imgui data into the framebuffer

	SDL_GL_SwapWindow( window );			// swap the double buffers

	// handle events
	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) {
		ImGui_ImplSDL2_ProcessEvent( &event );

		if ( event.type == SDL_QUIT )
			pquit = true;
		if ( event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID( window ) )
			pquit = true;
		if ( ( event.type == SDL_KEYUP  && event.key.keysym.sym == SDLK_ESCAPE ) || ( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_X1 ) ) //x1 is browser back on the mouse
			pquit = true;
	}
}


void physarum::quit () {
	//shutdown everything
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//destroy window
	SDL_GL_DeleteContext( GLcontext );
	SDL_DestroyWindow( window );
	SDL_Quit();

	cout << "goodbye." << endl;
}
