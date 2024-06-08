#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "pugixml.hpp"

#include "Circle.h"
#include "Group.h"
#include "Symbol.h"
#include "Instance_Symbol.h"
TEST(TestAnalyseXML, TestCircle) {
    std::string s = R"(<?xml version = "1.0"?>
                       <Circle label="testCircle" x="0" y="1" r="2" color="Black" />)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description(); // Si jamais result est faux, indique que le test est faux *et* affiche la string result.description() (qui contient la raison de l'erreur)
    Circle c{ doc.child("Circle") };
    std::string c_dump_ref =
R"(Circle "testCircle", x: 0, y: 1, r: 2, color: "Black"
)";
    EXPECT_EQ(c.dump(""), c_dump_ref);
}

TEST(TestAnalyseXML, TestGroup) {
    std::string s = R"(<?xml version = "1.0"?>
                       <Group label="testGroup" x="0" y="1">
                           <Circle label="testCircle1" x="2" y="3" r="4" color="Black"/>
                           <Circle label="testCircle2" x="5" y="6" r="7" color="Black"/>
                       </Group>)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description(); // Si jamais result est faux, indique que le test est faux *et* affiche la string result.description() (qui contient la raison de l'erreur)
    std::map<std::string, std::shared_ptr<Symbol>, std::less<>> symbols;
    Group g{ doc.child("Group"), symbols };
    std::string g_dump_ref =
R"(Group "testGroup", x: 0, y: 1, children: [
| Circle "testCircle1", x: 2, y: 3, r: 4, color: "Black"
| Circle "testCircle2", x: 5, y: 6, r: 7, color: "Black"
]
)";
    EXPECT_EQ(g.dump(""), g_dump_ref);
}

TEST(TestAnalyseXML, TestGroupHybrid) {
    std::string s = R"(<?xml version = "1.0"?>
                       <Group label="testGroupHybrid" x="0" y="1">
                            <Circle label="testCircle" x="2" y="3" r="4" color="Black"/>
                            <Group label="testGroup" x="5" y="6"/>
                       </Group>)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description(); // Si jamais result est faux, indique que le test est faux *et* affiche la string result.description() (qui contient la raison de l'erreur)
    std::map<std::string, std::shared_ptr<Symbol>, std::less<>> symbols;
    Group g{ doc.child("Group"), symbols };
    std::string g_dump_ref =
R"(Group "testGroupHybrid", x: 0, y: 1, children: [
| Circle "testCircle", x: 2, y: 3, r: 4, color: "Black"
| Group "testGroup", x: 5, y: 6, children: [
| ]
]
)";
    EXPECT_EQ(g.dump(""), g_dump_ref);
}

TEST(TestAnalyseXML, TestSymbolAndInstance) {
    std::string s_symb = R"(
<?xml version = "1.0"?>
<Symbol label="testSymbol">
    <Group label="testGroupHybrid" x="0" y="1">
         <Circle label="testCircle" x="2" y="3" r="4" color="Black"/>
         <Group label="testGroup" x="5" y="6"/>
    </Group>
</Symbol>)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s_symb.c_str());
    ASSERT_TRUE(result) << result.description(); // Si jamais result est faux, indique que le test est faux *et* affiche la string result.description() (qui contient la raison de l'erreur)
    std::map<std::string, std::shared_ptr<Symbol>, std::less<>> symbols;
    auto ps = std::make_shared<Symbol>( doc.child("Symbol"), symbols );
    std::string ps_dump_ref =
            R"(Symbol "testSymbol", children: [
| Group "testGroupHybrid", x: 0, y: 1, children: [
| | Circle "testCircle", x: 2, y: 3, r: 4, color: "Black"
| | Group "testGroup", x: 5, y: 6, children: [
| | ]
| ]
]
)";
    EXPECT_EQ(ps->dump_with_no_initial_indent(""), ps_dump_ref);

    std::string s_is = R"(
<?xml version = "1.0"?>
<Instance_Symbol label="testInstance" x="2" y="3" r="4" label_symbol="testSymbol" />
)";
    result = doc.load_string(s_is.c_str());
    ASSERT_TRUE(result) << result.description(); // Si jamais result est faux, indique que le test est faux *et* affiche la string result.description() (qui contient la raison de l'erreur)
    symbols[ doc.child("Instance_Symbol").attribute("label_symbol").as_string() ] = ps;
    Instance_Symbol is{ doc.child("Instance_Symbol"), symbols };
    std::string is_dump_ref =
            R"(Instance_Symbol "testInstance", x: 2, y: 3, Symbol "testSymbol", children: [
| Group "testGroupHybrid", x: 0, y: 1, children: [
| | Circle "testCircle", x: 2, y: 3, r: 4, color: "Black"
| | Group "testGroup", x: 5, y: 6, children: [
| | ]
| ]
]
)";
    EXPECT_EQ(is.dump(""), is_dump_ref);
}
