#include "gtest/gtest.h"
#include "../src/Base.h"
#include "../src/Tabla.h"

using namespace std;
Registro r ({"LU", "Año", "Nombre", "Carrera"}, {datoNat(0), datoNat(0), datoStr(""), datoStr("")});
Registro r2 ({},{});
Tabla t ({"LU", "Año", "Nombre", "Carrera"},
         { "LU", "Año" },
         { datoNat(0), datoNat(0), datoStr(""), datoStr("")});
Tabla t2({"Cod", "Carrera"}, {"Cod"},
         {datoNat(0), datoStr("")});


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
};