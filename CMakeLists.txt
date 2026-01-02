# Specify minimum supported cmake version
cmake_minimum_required(VERSION 3.10)

# Project TTV22SPMatematiikkaaJaFysiikkaaPeliohjelmoijille
project(TTV22SPMatematiikkaaJaFysiikkaaPeliohjelmoijille)

## Use C++20:
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ulkoiset kirjastot:
set(MIKROPLOT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("ext/mikroplot-main")
add_subdirectory("ext/imgui-master")
add_subdirectory("ext/glm-master")


# Include polut + filet:
include_directories("include")
file(GLOB_RECURSE GAME_MAT_PHYS_INC_FILES "./include/*.h")


# suoritattavat sovellukset:
add_executable(hello_world notebooks/main_hello_world.cpp ${GAME_MAT_PHYS_INC_FILES})
target_link_libraries(hello_world mikroplot)

# test_imgui - Esimerkki ImGUI:n käytöstä, jota saa käyttää, jos haluaa
#add_executable(test_imgui examples/test_imgui.cpp)
#target_link_libraries(test_imgui mikroplot imgui glm)

	#VK 1
#tunti tehtava 1
add_executable(1_nb_functions notebooks/main_funcions.cpp)

	#VK 2
#tunti tehtava 2
add_executable(2_simple_draw notebooks/main_simple_draw.cpp ${GAME_MAT_PHYS_INC_FILES})
target_link_libraries(2_simple_draw mikroplot)
#tunti tehtava 3
add_executable(3_newton_method notebooks/main_newton_method.cpp ${GAME_MAT_PHYS_INC_FILES})
target_link_libraries(3_newton_method mikroplot)

	#VK 3
#tunti tehtava 4
add_executable(4_simple_math notebooks/main_simple_math.cpp ${GAME_MAT_PHYS_INC_FILES})
target_link_libraries(4_simple_math mikroplot)

	#VK 4
#tunti tehtava 5
add_executable(5_aabb_collisionsm notebooks/main_aabb_collisions.cpp ${GAME_MAT_PHYS_INC_FILES})
target_link_libraries(5_aabb_collisionsm mikroplot glm)

	#VK 5
#tunti tehtava 6
add_executable(6_particles notebooks/main_particles.cpp ${GAME_MAT_PHYS_INC_FILES})
target_link_libraries(6_particles mikroplot glm imgui)
#tunti tehtava 7
add_executable(7_spring_force notebooks/main_spring.cpp ${GAME_MAT_PHYS_INC_FILES})
target_link_libraries(7_spring_force mikroplot glm imgui)

	#VK 6
#tunti tehtava 8
add_executable(8_point_rotation notebooks/main_point_rotation.cpp ${GAME_MAT_PHYS_INC_FILES})
target_link_libraries(8_point_rotation mikroplot glm imgui)
#tunti tehtava 9
add_executable(9_rotating_box notebooks/main_rotating_box.cpp ${GAME_MAT_PHYS_INC_FILES})
target_link_libraries(9_rotating_box mikroplot glm imgui)

#VK 7
#tunti tehtava 10
add_executable(10_car_physics notebooks/main_car_physics.cpp ${GAME_MAT_PHYS_INC_FILES})
target_link_libraries(10_car_physics mikroplot glm imgui)
#tunti tehtava 11
add_executable(11_collisions_with_mass notebooks/main_collisions_with_mass.cpp ${GAME_MAT_PHYS_INC_FILES})
target_link_libraries(11_collisions_with_mass mikroplot glm imgui)


#*************************************************************


#Kotitehtävä 1: Fuktioiden kuvaajien piirtäminen								DONE
add_executable(
	Fuktioiden_Kuvaajien_Piirtaminen 
	#include/FileWritingFunctions.h 
	submissions/t1/test_draw_functions.cpp ${GAME_MAT_PHYS_INC_FILES}
)
target_link_libraries(Fuktioiden_Kuvaajien_Piirtaminen mikroplot)


#Kotitehtävä 2: Numeerinen integrointi Newtonin menetelmällä					DONE
add_executable(
	Numeerinen_Integrointi_Newtonin_Menetelmalla 
	#include/FileWritingFunctions.h 
	submissions/t2/test_integration.cpp ${GAME_MAT_PHYS_INC_FILES}
)
target_link_libraries(Numeerinen_Integrointi_Newtonin_Menetelmalla mikroplot)


#Kotitehtävä 3: Vektorien ja matriisien toiminnallisuuden ohjelmointi			2p/6p
add_executable(
	Vektorien_Ja_Matriisien_Toiminnallisuuden_Ohjelmointi 
	#include/FileWritingFunctions.h 
	submissions/t3/test_math.cpp 
	submissions/t3/math.h submissions/t3/math.cpp
	submissions/t3/Tester.h submissions/t3/Testcases.h
	${GAME_MAT_PHYS_INC_FILES}
)
#target_link_libraries(Separated_axis_theorem mikroplot)


#Kotitehtävä 4: Separated axis theorem											4vai5?
add_executable(
	Separated_axis_theorem 
	#include/FileWritingFunctions.h 
	submissions/t3/math.h submissions/t3/math.cpp
	submissions/t4/test_sat.cpp 
	submissions/t4/sat.h
	${GAME_MAT_PHYS_INC_FILES}
)
target_link_libraries(Separated_axis_theorem glm mikroplot)


#Kotitehtävä 5: Partikkelit														4vai5?
add_executable(
	Particles 
	#include/FileWritingFunctions.h 
	submissions/t5/particle_demo.cpp
	${GAME_MAT_PHYS_INC_FILES}
)
target_link_libraries(Particles glm mikroplot imgui)


#Kotitehtävä 6: Jousivoima														2/3
add_executable(
	Spring 
	#include/FileWritingFunctions.h 
	submissions/t6/spring_demo.cpp
	${GAME_MAT_PHYS_INC_FILES}
)
target_link_libraries(Spring glm mikroplot imgui)


#Kotitehtävä 7: Massallinen törmäys												DONE?
add_executable(
	CollisionDemo 
	#include/FileWritingFunctions.h 
	submissions/t7/collision_demo.cpp
	${GAME_MAT_PHYS_INC_FILES}
)
target_link_libraries(CollisionDemo mikroplot glm)


#Kotitehtävä 8: Yksinkertainen autopelin fysiikka								...
add_executable(
	CarDemo 
	#include/FileWritingFunctions.h 
	submissions/t8/car_demo.cpp
	submissions/t8/car.h
	submissions/t8/gameobject.h
	${GAME_MAT_PHYS_INC_FILES}
)
target_link_libraries(CarDemo mikroplot glm)


#Kotitehtävä Harkka: ...														...	
add_executable(
	Harkka
	submissions/practical_work/physics_demo.cpp
	submissions/practical_work/harkka.h
	${GAME_MAT_PHYS_INC_FILES}
)
target_link_libraries(Harkka mikroplot glm imgui)


#*************************************************************


#Harkkatyö:
#		idea:
# - yksinkertainen fysiikkamoottori
#

#	make headers for functions and screenshot creation?
#	what functions to use?
#	How do the cmath functions work?
#	SINE = https://youtu.be/kkMt4lrJzs8