#include "gtest/gtest.h"
#include "../src/Base.h"
#include "../src/Tabla.h"

using namespace std;
Registro r ({"LU", "Año", "Nombre", "Carrera"}, {datoNat(0), datoNat(0), datoStr(""), datoStr("")});
Registro r2 ({"Cod", "Carrera"},{datoNat(10), datoStr("af")});
Registro r3 ({"mal"}, {datoNat(666)});
Registro r4 ({"LU", "Año", "Nombre", "Carrera"}, {datoNat(150), datoNat(0), datoStr(""), datoStr("")});

Tabla t ({"LU", "Año", "Nombre", "Carrera"},
         { "LU", "Año" },
         { datoNat(10), datoNat(8560), datoStr("A"), datoStr("B")});
Tabla t2({"Cod", "Carrera"}, {"Cod"},
         {datoNat(150), datoStr("asdf")});
Tabla t3 ({"LU", "Año", "Nombre", "Carrera"},
         { "LU", "Año" },
         { datoNat(0), datoNat(0), datoStr(""), datoStr("")} );


Criterio c1({make_tuple("LU",datoNat(0), true)});
Criterio c2({make_tuple("LU",datoNat(0), false)});
Criterio c3({make_tuple("LU",datoNat(0), true),make_tuple("Año",datoNat(0), true)});
Criterio cr1({make_tuple("LU",datoNat(20), true)});
Criterio cr2({make_tuple("LU",datoNat(20), false)});
Criterio cr3({make_tuple("LU",datoNat(20), true),make_tuple("Año",datoNat(20), true)});
Criterio cr4({make_tuple("LU",datoNat(20), false),make_tuple("Año",datoNat(20), false)});





class BaseTests : public ::testing::Test {

protected:
    BaseTests() :   b({"tabla1","tabla2"},{t,t2},{}),
                    b3({"tabla1","tabla2"},{t,t2},{}),
                    b2({"tablaB","tablaA"},{t2,t},{}){};

    Base b;
    Base b2;
    Base b3;

};




TEST (base_test,  crear){
    Base b({"tabla1","tabla2"},{t,t2},{});
    Base b2({"tablaB","tablaA"},{t2,t},{});
};




TEST_F (BaseTests, tablaDefinida){
    b.agregarTabla("tabla3",t);
    b.agregarTabla("tabla1",t2);
    EXPECT_EQ(b.tablaDefinida("tabla1"), true);
    EXPECT_EQ(b.tablaDefinida("tabla20"), false);
    EXPECT_EQ(b.tablaDefinida("tabla3"), true);
    EXPECT_EQ(b.nombre().back(), "tabla3");
    EXPECT_EQ(b.nombre().size(), 3);

    EXPECT_DEATH(b.obtenerTabla("asdf"),"");

};


TEST_F (BaseTests, estaDefinidoEn){

    EXPECT_EQ(b.estaDefinidoEn("tabla1", r), false);
    EXPECT_EQ(b.estaDefinidoEn("tabla2", r2),false);
    b.agregarRegistroATabla("tabla1",r);
    b.agregarRegistroATabla("tabla2",r2);
    EXPECT_EQ(b.estaDefinidoEn("tabla1", r), true);
    EXPECT_EQ(b.estaDefinidoEn("tabla2", r2), true);
    EXPECT_EQ(b.estaDefinidoEn("tabla1", r3), false);
    b.agregarRegistroATabla("tabla2",r3);
    EXPECT_EQ(b.estaDefinidoEn("tabla1", r3), false);


};

TEST_F (BaseTests, Busqueda) {
    EXPECT_EQ(b.busqueda("tabla1", c1),t);
    b.agregarRegistroATabla("tabla1",r);
    b.agregarTabla("tabla3", b.busqueda("tabla1", cr1));
    b.agregarTabla("tabla4", b.busqueda("tabla1", cr2));
    b.agregarTabla("tabla3b", b.busqueda("tabla1", c1));
    b.agregarTabla("tabla4b", b.busqueda("tabla1", c2));

    EXPECT_FALSE(b.estaDefinidoEn("tabla3",r));
    EXPECT_TRUE(b.estaDefinidoEn("tabla3b",r));

    EXPECT_TRUE(b.estaDefinidoEn("tabla4",r));
    EXPECT_FALSE(b.estaDefinidoEn("tabla4b",r));

    b.agregarRegistroATabla("tabla1",r4);
    b.agregarTabla("tabla5", b.busqueda("tabla1", cr3));
    b.agregarTabla("tabla6", b.busqueda("tabla1", cr4));
    b.agregarTabla("tabla7", b.busqueda("tabla1",c3));

    EXPECT_FALSE(b.estaDefinidoEn("tabla5",r));
    EXPECT_FALSE(b.estaDefinidoEn("tabla5",r4));

    EXPECT_TRUE(b.estaDefinidoEn("tabla6",r));
    EXPECT_TRUE(b.estaDefinidoEn("tabla6",r4));

    EXPECT_TRUE(b.estaDefinidoEn("tabla7",r));

    EXPECT_DEATH(b.busqueda("tabla2", c1),"");

}

TEST_F(BaseTests, operador){
   EXPECT_TRUE(b==b);
    EXPECT_TRUE(b==b3);
    EXPECT_FALSE(b==b2);

    b.agregarTabla("tabla5", b.busqueda("tabla1", cr3));
    b.agregarTabla("tabla6", b.busqueda("tabla1", cr4));
    b.agregarTabla("tabla7", b.busqueda("tabla1", c3));

    b3.agregarTabla("tabla7", b.busqueda("tabla1", c3));
    b3.agregarTabla("tabla6", b.busqueda("tabla1", cr4));
    b3.agregarTabla("tabla5", b.busqueda("tabla1", cr3));

    EXPECT_TRUE(b==b3);

}