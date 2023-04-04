#include <gtest/gtest.h>

#include "Comunidad.h"

using namespace std;

TEST(Comunidad, vacia) {
    Comunidad cm;
    
    EXPECT_EQ(0, cm.cantidad_asociaciones());
    EXPECT_EQ(set<int>(), cm.inscriptos());
}

TEST(Comunidad, agregar_usuarios_ver_ids) {
    Comunidad cm;

    cm.inscribir("Empresa A", 1);
    cm.inscribir("Empresa B", 2);
    cm.inscribir("Empresa C", 3);

    set<int> u = {1,2,3};
    EXPECT_EQ(u, cm.inscriptos());

    cm.inscribir("Empresa D", 4);
    cm.inscribir("Empresa E", 5);
    
    u = {1,2,3,4,5};
    EXPECT_EQ(u, cm.inscriptos());
}

TEST(Comunidad, agregar_usuarios_ver_empresa) {
    Comunidad cm;

    cm.inscribir("Empresa C", 3);
    cm.inscribir("Empresa B", 2);
    cm.inscribir("Empresa A", 1);

    EXPECT_EQ("Empresa C", cm.obtener_empresa(3));
    EXPECT_EQ("Empresa B", cm.obtener_empresa(2));
    EXPECT_EQ("Empresa A", cm.obtener_empresa(1));
}

TEST(Comunidad, agregar_usuarios_ver_socios) {
    Comunidad cm;

    cm.inscribir("Empresa C", 3);
    cm.inscribir("Empresa B", 2);
    cm.inscribir("Empresa A", 1);

    EXPECT_EQ(0, cm.cantidad_asociaciones());
    EXPECT_EQ(set<string>(), cm.obtener_socios(3));
    EXPECT_EQ(set<string>(), cm.obtener_socios(2));
    EXPECT_EQ(set<string>(), cm.obtener_socios(1));
}

TEST(Comunidad, desinscribir_ver_ids) {
    Comunidad cm;

    cm.inscribir("Empresa A", 1);
    cm.inscribir("Empresa B", 2);
    cm.inscribir("Empresa C", 3);
    cm.inscribir("Empresa D", 4);
    cm.inscribir("Empresa E", 5);

    cm.desinscribir(2);
    cm.desinscribir(3);

    set<int> u = {1,4,5};
    EXPECT_EQ(u, cm.inscriptos());
    
    cm.desinscribir(1);
    cm.desinscribir(4);
    cm.desinscribir(5);

    u = {};
    EXPECT_EQ(u, cm.inscriptos());
}

TEST(Comunidad, asociar_ver_socios) {
    Comunidad cm;

    cm.inscribir("Empresa A", 5);
    cm.inscribir("Empresa B", 4);
    cm.inscribir("Empresa C", 3);
    cm.inscribir("Empresa D", 2);
    cm.inscribir("Empresa E", 1);
    cm.inscribir("Empresa F", 0);

    cm.asociar("Empresa E","Empresa D");

    EXPECT_EQ(1, cm.cantidad_asociaciones());
    set<string> u = {"Empresa D"};
    EXPECT_EQ(u, cm.obtener_socios(1));
    u = {"Empresa E"};
    EXPECT_EQ(u, cm.obtener_socios(2));

    cm.asociar("Empresa E","Empresa C");
    cm.asociar("Empresa B","Empresa A");

    EXPECT_EQ(3, cm.cantidad_asociaciones());
    u = {"Empresa D", "Empresa C"};
    EXPECT_EQ(u, cm.obtener_socios(1));
    u = {"Empresa E"};
    EXPECT_EQ(u, cm.obtener_socios(2));
    u = {"Empresa E"};
    EXPECT_EQ(u, cm.obtener_socios(3));
    u = {"Empresa A"};
    EXPECT_EQ(u, cm.obtener_socios(4));
    u = {"Empresa B"};
    EXPECT_EQ(u, cm.obtener_socios(5));
}

TEST(Comunidad, desasociar_ver_socios) {
    Comunidad cm;

    cm.inscribir("Empresa A", 5);
    cm.inscribir("Empresa B", 4);
    cm.inscribir("Empresa C", 3);
    cm.inscribir("Empresa D", 2);
    cm.inscribir("Empresa E", 1);
    cm.inscribir("Empresa F", 0);

    cm.asociar("Empresa E","Empresa D");
    cm.asociar("Empresa E","Empresa C");
    cm.asociar("Empresa B","Empresa A");
    cm.desasociar("Empresa E","Empresa D");

    EXPECT_EQ(2, cm.cantidad_asociaciones());
    set<string> u = {"Empresa C"};
    EXPECT_EQ(u, cm.obtener_socios(1));
    u = {};
    EXPECT_EQ(u, cm.obtener_socios(2));
    u = {"Empresa E"};
    EXPECT_EQ(u, cm.obtener_socios(3));
    u = {"Empresa A"};
    EXPECT_EQ(u, cm.obtener_socios(4));
    u = {"Empresa B"};
    EXPECT_EQ(u, cm.obtener_socios(5));
}

TEST(Comunidad, desinscribir_ver_socios) {
    Comunidad cm;

    cm.inscribir("Empresa A", 5);
    cm.inscribir("Empresa B", 4);
    cm.inscribir("Empresa C", 3);
    cm.inscribir("Empresa D", 2);
    cm.inscribir("Empresa E", 1);
    cm.inscribir("Empresa F", 0);

    cm.asociar("Empresa E","Empresa D");
    cm.asociar("Empresa E","Empresa C");
    cm.asociar("Empresa B","Empresa A");

    cm.desinscribir(1);

    EXPECT_EQ(1, cm.cantidad_asociaciones());
    set<string> u = {};
    EXPECT_EQ(u, cm.obtener_socios(2));
    u = {};
    EXPECT_EQ(u, cm.obtener_socios(3));
    u = {"Empresa A"};
    EXPECT_EQ(u, cm.obtener_socios(4));
    u = {"Empresa B"};
    EXPECT_EQ(u, cm.obtener_socios(5));
}

TEST(Comunidad, obtener_id) {
    Comunidad cm;

    cm.inscribir("Empresa A", 5);
    cm.inscribir("Empresa B", 0);
    cm.inscribir("Empresa C", 27);

    EXPECT_EQ(5, cm.obtener_id("Empresa A"));
    EXPECT_EQ(0, cm.obtener_id("Empresa B"));
    EXPECT_EQ(27, cm.obtener_id("Empresa C"));
}

TEST(Comunidad, asociar_verificar_empresa_popular) {
    Comunidad cm;

    cm.inscribir("Empresa A", 5);
    cm.inscribir("Empresa B", 4);
    cm.inscribir("Empresa C", 3);
    cm.inscribir("Empresa D", 2);
    cm.inscribir("Empresa E", 1);
    cm.inscribir("Empresa F", 0);

    cm.asociar("Empresa E","Empresa D");
    cm.asociar("Empresa B","Empresa A");
    cm.asociar("Empresa B","Empresa C");
    cm.asociar("Empresa D","Empresa B");
    cm.asociar("Empresa E","Empresa B");
    cm.asociar("Empresa F","Empresa B");

    EXPECT_TRUE(cm.es_empresa_popular("Empresa B"));
    EXPECT_FALSE(cm.es_empresa_popular("Empresa A"));
    EXPECT_FALSE(cm.es_empresa_popular("Empresa C"));
    EXPECT_FALSE(cm.es_empresa_popular("Empresa D"));
    EXPECT_FALSE(cm.es_empresa_popular("Empresa E"));
    EXPECT_FALSE(cm.es_empresa_popular("Empresa F"));

    cm.asociar("Empresa E","Empresa A");
    cm.asociar("Empresa E","Empresa C");
    cm.asociar("Empresa E","Empresa F");

    EXPECT_TRUE(cm.es_empresa_popular("Empresa B"));
    EXPECT_FALSE(cm.es_empresa_popular("Empresa A"));
    EXPECT_FALSE(cm.es_empresa_popular("Empresa C"));
    EXPECT_FALSE(cm.es_empresa_popular("Empresa D"));
    EXPECT_TRUE(cm.es_empresa_popular("Empresa E"));
    EXPECT_FALSE(cm.es_empresa_popular("Empresa F"));
}

TEST(Comunidad, desasociar_empresa_popular_cambia) {
    Comunidad cm;

    cm.inscribir("Empresa A", 5);
    cm.inscribir("Empresa B", 4);
    cm.inscribir("Empresa C", 3);
    cm.inscribir("Empresa D", 2);
    cm.inscribir("Empresa E", 1);
    cm.inscribir("Empresa F", 0);

    cm.asociar("Empresa E","Empresa D");
    cm.asociar("Empresa B","Empresa A");
    cm.asociar("Empresa B","Empresa C");
    cm.asociar("Empresa D","Empresa B");
    cm.asociar("Empresa E","Empresa B");
    cm.asociar("Empresa F","Empresa B");

    EXPECT_TRUE(cm.es_empresa_popular("Empresa B"));

    cm.desasociar("Empresa B","Empresa A");

    EXPECT_FALSE(cm.es_empresa_popular("Empresa B"));
}

TEST(Comunidad, desasociar_empresa_popular_no_cambia) {
    Comunidad cm;

    cm.inscribir("Empresa A", 5);
    cm.inscribir("Empresa B", 4);
    cm.inscribir("Empresa C", 3);
    cm.inscribir("Empresa D", 2);
    cm.inscribir("Empresa E", 1);
    cm.inscribir("Empresa F", 0);

    cm.asociar("Empresa E","Empresa D");
    cm.asociar("Empresa B","Empresa A");
    cm.asociar("Empresa B","Empresa C");
    cm.asociar("Empresa D","Empresa B");
    cm.asociar("Empresa E","Empresa B");
    cm.asociar("Empresa F","Empresa B");

    EXPECT_TRUE(cm.es_empresa_popular("Empresa B"));

    cm.desasociar("Empresa E","Empresa D");

    EXPECT_TRUE(cm.es_empresa_popular("Empresa B"));
}

TEST(Comunidad, desinscribir_ver_empresa_popular_cambia) {
    Comunidad cm;

    cm.inscribir("Empresa A", 5);
    cm.inscribir("Empresa B", 4);
    cm.inscribir("Empresa C", 3);
    cm.inscribir("Empresa D", 2);
    cm.inscribir("Empresa E", 1);
    cm.inscribir("Empresa F", 0);

    cm.asociar("Empresa E","Empresa D");
    cm.asociar("Empresa B","Empresa A");
    cm.asociar("Empresa B","Empresa C");
    cm.asociar("Empresa D","Empresa B");
    cm.asociar("Empresa E","Empresa B");
    cm.asociar("Empresa F","Empresa B");

    EXPECT_TRUE(cm.es_empresa_popular("Empresa B"));

    cm.desinscribir(0);

    EXPECT_FALSE(cm.es_empresa_popular("Empresa B"));
}

TEST(Comunidad, desinscribir_ver_empresa_popular_no_cambia) {
    Comunidad cm;

    cm.inscribir("Empresa A", 5);
    cm.inscribir("Empresa B", 4);
    cm.inscribir("Empresa C", 3);
    cm.inscribir("Empresa D", 2);
    cm.inscribir("Empresa E", 1);
    cm.inscribir("Empresa F", 0);
    cm.inscribir("Empresa G", -1);
    cm.inscribir("Empresa H", -2);

    cm.asociar("Empresa E","Empresa D");
    cm.asociar("Empresa E","Empresa H");
    cm.asociar("Empresa B","Empresa A");
    cm.asociar("Empresa B","Empresa C");
    cm.asociar("Empresa D","Empresa B");
    cm.asociar("Empresa E","Empresa B");
    cm.asociar("Empresa F","Empresa B");
    cm.asociar("Empresa G","Empresa B");

    EXPECT_TRUE(cm.es_empresa_popular("Empresa B"));

    cm.desinscribir(-1);
    cm.desinscribir(-2);

    EXPECT_TRUE(cm.es_empresa_popular("Empresa B"));
}