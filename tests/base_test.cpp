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



class BaseTests : public ::testing::Test {

protected:
    BaseTests() :   b({"tabla1","tabla2"},{t,t2}),
                    b2({"tablaB","tablaA"},{t2,t}){};

    Base b;
    Base b2;

};




TEST (base_test,  crear){
    Base b({"tabla1","tabla2"},{t,t2});
    Base b2({"tablaB","tablaA"},{t2,t});
};




TEST_F (BaseTests, tablaDefinida){
    b.agregarTabla("tabla3",t);
    b.agregarTabla("tabla1",t2);
    EXPECT_EQ(b.tablaDefinida("tabla1"), true);
    EXPECT_EQ(b.tablaDefinida("tabla20"), false);
    EXPECT_EQ(b.tablaDefinida("tabla3"), true);
    EXPECT_EQ(b.nombre().back(), "tabla3");
    EXPECT_EQ(b.nombre().size(), 3);


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
    //EXPECT_EQ(b.busqueda("tabla1", true,"LU",datoNat(10)),t);
    b.agregarRegistroATabla("tabla1",r);
    //b.agregarTabla("tabla3", b.busqueda("tabla1", true,"LU",datoNat(10)));
    //b.agregarTabla("tabla4", b.busqueda("tabla1", false,"LU",datoNat(10)));

    //EXPECT_FALSE(b.estaDefinidoEn("tabla3",r));

    //EXPECT_TRUE(b.estaDefinidoEn("tabla4",r));

    b.agregarRegistroATabla("tabla1",r4);
    //b.agregarTabla("tabla5", b.busqueda("tabla1", true,"LU",datoNat(10)));
    b.agregarTabla("tabla6", b.busqueda("tabla1", false,"LU",datoNat(26)));

    //EXPECT_FALSE(b.estaDefinidoEn("tabla5",r));
    //EXPECT_FALSE(b.estaDefinidoEn("tabla5",r4));

    EXPECT_TRUE(b.estaDefinidoEn("tabla6",r));
    EXPECT_TRUE(b.estaDefinidoEn("tabla6",r4));

}