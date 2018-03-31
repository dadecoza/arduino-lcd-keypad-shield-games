#include <avr/pgmspace.h>

#define areaStart                     0
#define areaStartOpt1                 1
#define areaStartOpt2                 2
#define areaStartOpt3                 3
#define areaStartOpt4                 4
#define areaLitWoodText               5
#define areaLitWoodText_noMouse       6
#define areaLitWoodOpt3               7
#define areaLitWoodOpt3mouse          8
#define areaCaveText                  9
#define areaCaveText_frisbee         10
#define areaCaveOpt1                 11
#define areaCaveOpt1_frisbee         12
#define areaCaveOpt1_wave            13
#define areaCaveOpt2                 14
#define areaCar                      15
#define areaInsideCar                16
#define areaInsideCarOpt2            17
#define areaCarParts                 18
#define areaCarParts_comp            19
#define areaCarPartsPockets          20
#define areaInsideCompleteCar        21
#define areaInsideCompleteCarOpt1    22
#define areaInsideCompleteCarOpt1_CD 23
#define areaCottage                  24
#define areaCottageOpt2              25
#define areaInsideCottage            26
#define areaInsideCottage_keys       27
#define areaInsideCottage_cd         28
#define areaInsideCottageOpt1        29
#define areaInsideCottageOpt1_mouse  30
#define areaInsideCottageOpt1_stroke 31
#define areaInsideCottageOpt2        32
#define areaInsideCottageOpt2_takeCD 33
#define areaInsideCottageOpt2_play   34
#define areaGarden                   35
#define areaGardenOpt4               36
#define areaShed                     37
#define areaShed_frisbee             38
#define areaShedOpt1                 39
#define areaShedOpt1_can             40
#define areaShedOpt1_got             41
#define areaShedOpt2                 42
#define areaShedOpt4                 43
#define areaWell                     44
#define areaWell_mirror              45
#define areaWellOpt1                 46
#define areaWellOpt1_rope            47
#define areaWellOpt1_hook            48
#define areaWellOpt1_coin            49
#define areaOuthouse                 50
#define areaOuthouse_hook            51
#define areaOuthouseOpt3             52
#define areaOuthouseOpt3_hook        53
#define areaOuthouseOpt3_wee         54
#define areaBeach                    55
#define areaBeach_snail              56
#define areaBeachOpt3                57
#define areaBeachOpt3_search         58
#define areaBoat                     59
#define areaBoatOpt1                 60
#define areaBoatOpt2                 61
#define areaBoatOpt2_can             62
#define areaBoatOpt2_dneed           63
#define areaBoatOpt3                 64
#define areaBoatOpt3_dneed           65
#define areaFinish                   66
#define areaCredits                  67
#define areaAmyCredits               68
#define areaIntro                    69

const char text_0[] PROGMEM = "You awaken";
const char text_1[] PROGMEM = "surrounded by";
const char text_2[] PROGMEM = "trees, it's";
const char text_3[] PROGMEM = "dark and your";
const char text_4[] PROGMEM = "back aches from";
const char text_5[] PROGMEM = "the damp";
const char text_6[] PROGMEM = "ground. Your";
const char text_7[] PROGMEM = "heart pounds in";
const char text_8[] PROGMEM = "your chest.";
const char text_9[] PROGMEM = "What should you";
const char text_10[] PROGMEM = "do?";
const char text_11[] PROGMEM = "1. Scream like";
const char text_12[] PROGMEM = "a girl.";
const char text_13[] PROGMEM = "2. Check your";
const char text_14[] PROGMEM = "pockets.";
const char text_15[] PROGMEM = "3. Run like";
const char text_16[] PROGMEM = "crazy in a";
const char text_17[] PROGMEM = "random";
const char text_18[] PROGMEM = "direction.";
const char text_19[] PROGMEM = "4. Look around";
const char text_20[] PROGMEM = "the clearing.";
const char text_21[] PROGMEM = "You scream";
const char text_22[] PROGMEM = "pathetically";
const char text_23[] PROGMEM = "like a girl.";
const char text_24[] PROGMEM = "You stand there";
const char text_25[] PROGMEM = "and wet";
const char text_26[] PROGMEM = "yourself as you";
const char text_27[] PROGMEM = "hear wolves";
const char text_28[] PROGMEM = "approaching";
const char text_29[] PROGMEM = "from all";
const char text_30[] PROGMEM = "directions.";
const char text_31[] PROGMEM = "Press any";
const char text_32[] PROGMEM = "button to";
const char text_33[] PROGMEM = "continue.";
const char text_34[] PROGMEM = "Rummaging";
const char text_35[] PROGMEM = "through your";
const char text_36[] PROGMEM = "pockets, you";
const char text_37[] PROGMEM = "find";
const char text_38[] PROGMEM = "a smashed";
const char text_39[] PROGMEM = "phone, a torch,";
const char text_40[] PROGMEM = "a rubber duck,";
const char text_41[] PROGMEM = "and a large";
const char text_42[] PROGMEM = "brass trumpet.";
const char text_43[] PROGMEM = "You switch on";
const char text_44[] PROGMEM = "the torch and";
const char text_45[] PROGMEM = "throw away";
const char text_46[] PROGMEM = "the other";
const char text_47[] PROGMEM = "stuff.";
const char text_48[] PROGMEM = "Press any";
const char text_49[] PROGMEM = "button to";
const char text_50[] PROGMEM = "continue.";
const char text_51[] PROGMEM = "Running like";
const char text_52[] PROGMEM = "crazy, you cant";
const char text_53[] PROGMEM = "see where";
const char text_54[] PROGMEM = "you are going.";
const char text_55[] PROGMEM = "You hear a roar";
const char text_56[] PROGMEM = "and";
const char text_57[] PROGMEM = "something";
const char text_58[] PROGMEM = "fluffy hits you";
const char text_59[] PROGMEM = "on the head.";
const char text_60[] PROGMEM = "In the darkness";
const char text_61[] PROGMEM = "you think you";
const char text_62[] PROGMEM = "can make";
const char text_63[] PROGMEM = "out a bear's";
const char text_64[] PROGMEM = "face inches";
const char text_65[] PROGMEM = "from your own.";
const char text_66[] PROGMEM = "You fall";
const char text_67[] PROGMEM = "unconscious and";
const char text_68[] PROGMEM = "sleep a while.";
const char text_69[] PROGMEM = "Press any";
const char text_70[] PROGMEM = "button to";
const char text_71[] PROGMEM = "continue.";
const char text_72[] PROGMEM = "It's dark, so";
const char text_73[] PROGMEM = "you obviously";
const char text_74[] PROGMEM = "can't see";
const char text_75[] PROGMEM = "anything.";
const char text_76[] PROGMEM = "Stupid.";
const char text_77[] PROGMEM = "Press any";
const char text_78[] PROGMEM = "button to";
const char text_79[] PROGMEM = "continue.";
const char text_80[] PROGMEM = "You are in a";
const char text_81[] PROGMEM = "clearing in the";
const char text_82[] PROGMEM = "woods. Tire";
const char text_83[] PROGMEM = "tracks lead one";
const char text_84[] PROGMEM = "way, and a path";
const char text_85[] PROGMEM = "towards";
const char text_86[] PROGMEM = "a cave leads";
const char text_87[] PROGMEM = "the other way.";
const char text_88[] PROGMEM = "There is a dead";
const char text_89[] PROGMEM = "mouse on the";
const char text_90[] PROGMEM = "ground.";
const char text_91[] PROGMEM = "What should you";
const char text_92[] PROGMEM = "do?";
const char text_93[] PROGMEM = "1. Follow the";
const char text_94[] PROGMEM = "tire tracks.";
const char text_95[] PROGMEM = "2. Make your";
const char text_96[] PROGMEM = "way to the";
const char text_97[] PROGMEM = "cave.";
const char text_98[] PROGMEM = "3. Pick up the";
const char text_99[] PROGMEM = "dead mouse.";
const char text_100[] PROGMEM = "You are in a";
const char text_101[] PROGMEM = "clearing in the";
const char text_102[] PROGMEM = "Woods. Tire";
const char text_103[] PROGMEM = "tracks lead one";
const char text_104[] PROGMEM = "way, and a path";
const char text_105[] PROGMEM = "towards";
const char text_106[] PROGMEM = "a cave leads";
const char text_107[] PROGMEM = "the other way.";
const char text_108[] PROGMEM = "What should you";
const char text_109[] PROGMEM = "do?";
const char text_110[] PROGMEM = "1. Follow the";
const char text_111[] PROGMEM = "tire tracks.";
const char text_112[] PROGMEM = "2. Make your";
const char text_113[] PROGMEM = "way to the";
const char text_114[] PROGMEM = "cave.";
const char text_115[] PROGMEM = "Ugh, why would";
const char text_116[] PROGMEM = "you want to";
const char text_117[] PROGMEM = "pick that up?";
const char text_118[] PROGMEM = "You decide to";
const char text_119[] PROGMEM = "leave the dead";
const char text_120[] PROGMEM = "mouse where";
const char text_121[] PROGMEM = "it is.";
const char text_122[] PROGMEM = "Press any";
const char text_123[] PROGMEM = "button to";
const char text_124[] PROGMEM = "continue.";
const char text_125[] PROGMEM = "You carefully";
const char text_126[] PROGMEM = "pick up the";
const char text_127[] PROGMEM = "dead mouse and";
const char text_128[] PROGMEM = "pop it in your";
const char text_129[] PROGMEM = "pocket.";
const char text_130[] PROGMEM = "Press any";
const char text_131[] PROGMEM = "button to";
const char text_132[] PROGMEM = "continue.";
const char text_133[] PROGMEM = "You find"; //areaCaveText
const char text_134[] PROGMEM = "yourself in a";
const char text_135[] PROGMEM = "cave. A bear";
const char text_136[] PROGMEM = "sits";
const char text_137[] PROGMEM = "in the corner";
const char text_138[] PROGMEM = "holding a";
const char text_139[] PROGMEM = "steering wheel.";
const char text_140[] PROGMEM = "Bats are";
const char text_141[] PROGMEM = "flapping about,";
const char text_142[] PROGMEM = "and a path from";
const char text_143[] PROGMEM = "the cave leads";
const char text_144[] PROGMEM = "to a wooded";
const char text_145[] PROGMEM = "area.";
const char text_146[] PROGMEM = "What should you";
const char text_147[] PROGMEM = "do?";
const char text_148[] PROGMEM = "1. Try taking";
const char text_149[] PROGMEM = "steering wheel";
const char text_150[] PROGMEM = "from bear.";
const char text_151[] PROGMEM = "2. Poke at the";
const char text_152[] PROGMEM = "bats.";
const char text_153[] PROGMEM = "3. Exit cave";
const char text_154[] PROGMEM = "and follow path";
const char text_155[] PROGMEM = "to woods.";
const char text_156[] PROGMEM = "You find"; //areaCaveText_frisbee
const char text_157[] PROGMEM = "yourself in a";
const char text_158[] PROGMEM = "cave. A bear";
const char text_159[] PROGMEM = "sits";
const char text_160[] PROGMEM = "happily in the";
const char text_161[] PROGMEM = "corner holding";
const char text_162[] PROGMEM = "a frisbee.";
const char text_163[] PROGMEM = "Bats are";
const char text_164[] PROGMEM = "flapping about,";
const char text_165[] PROGMEM = "and a path from";
const char text_166[] PROGMEM = "the cave leads";
const char text_167[] PROGMEM = "to a wooded";
const char text_168[] PROGMEM = "area.";
const char text_169[] PROGMEM = "What should you";
const char text_170[] PROGMEM = "do?";
const char text_171[] PROGMEM = "1. Wave at the";
const char text_172[] PROGMEM = "bear.";
const char text_173[] PROGMEM = "2. Poke a stick";
const char text_174[] PROGMEM = "at the bats.";
const char text_175[] PROGMEM = "3. Exit cave";
const char text_176[] PROGMEM = "and follow path";
const char text_177[] PROGMEM = "to woods.";
const char text_178[] PROGMEM = "The bear growls"; //areaCaveOpt1
const char text_179[] PROGMEM = "at you as you";
const char text_180[] PROGMEM = "approach.";
const char text_181[] PROGMEM = "Ignoring it's";
const char text_182[] PROGMEM = "warning, you";
const char text_183[] PROGMEM = "attempt to";
const char text_184[] PROGMEM = "snatch the";
const char text_185[] PROGMEM = "steering wheel.";
const char text_186[] PROGMEM = "The bear roars";
const char text_187[] PROGMEM = "and chews your";
const char text_188[] PROGMEM = "face off.";
const char text_189[] PROGMEM = "Press any";
const char text_190[] PROGMEM = "button to";
const char text_191[] PROGMEM = "continue.";
const char text_192[] PROGMEM = "The bear growls"; //areaCaveOpt1_frisbee
const char text_193[] PROGMEM = "as you";
const char text_194[] PROGMEM = "approach.";
const char text_195[] PROGMEM = "You throw the";
const char text_196[] PROGMEM = "frisbee at the";
const char text_197[] PROGMEM = "bear. He";
const char text_198[] PROGMEM = "catches it and";
const char text_199[] PROGMEM = "passes you the";
const char text_200[] PROGMEM = "steering";
const char text_201[] PROGMEM = "wheel.";
const char text_202[] PROGMEM = "Press any";
const char text_203[] PROGMEM = "button to";
const char text_204[] PROGMEM = "continue.";
const char text_205[] PROGMEM = "The bear waves"; //areaCaveOpt1_wave
const char text_206[] PROGMEM = "his frisbee at";
const char text_207[] PROGMEM = "you.";
const char text_208[] PROGMEM = "Press any";
const char text_209[] PROGMEM = "button to";
const char text_210[] PROGMEM = "continue.";
const char text_211[] PROGMEM = "You poke the"; //areaCaveOpt2
const char text_212[] PROGMEM = "bats but";
const char text_213[] PROGMEM = "nothing";
const char text_214[] PROGMEM = "happens.";
const char text_215[] PROGMEM = "At a glance,";
const char text_216[] PROGMEM = "you thought";
const char text_217[] PROGMEM = "that one of";
const char text_218[] PROGMEM = "them looked";
const char text_219[] PROGMEM = "just like";
const char text_220[] PROGMEM = "IceBat.";
const char text_221[] PROGMEM = "Press any";
const char text_222[] PROGMEM = "button to";
const char text_223[] PROGMEM = "continue.";
const char text_224[] PROGMEM = "There is a"; //areaCar
const char text_225[] PROGMEM = "rusty old car,";
const char text_226[] PROGMEM = "it's a bit";
const char text_227[] PROGMEM = "beat up, but";
const char text_228[] PROGMEM = "looks";
const char text_229[] PROGMEM = "roadworthy and";
const char text_230[] PROGMEM = "it";
const char text_231[] PROGMEM = "appears to be";
const char text_232[] PROGMEM = "unlocked.";
const char text_233[] PROGMEM = "There is a";
const char text_234[] PROGMEM = "pretty cottage";
const char text_235[] PROGMEM = "nearby.";
const char text_236[] PROGMEM = "What should you";
const char text_237[] PROGMEM = "do?";
const char text_238[] PROGMEM = "1. Follow tire";
const char text_239[] PROGMEM = "tracks back to";
const char text_240[] PROGMEM = "the woods.";
const char text_241[] PROGMEM = "2. Head towards";
const char text_242[] PROGMEM = "the cottage.";
const char text_243[] PROGMEM = "3. Get in the";
const char text_244[] PROGMEM = "car.";
const char text_245[] PROGMEM = "You are in"; //areaInsideCar
const char text_246[] PROGMEM = "driver seat.";
const char text_247[] PROGMEM = "It's pretty";
const char text_248[] PROGMEM = "comfortable,";
const char text_249[] PROGMEM = "but you notice";
const char text_250[] PROGMEM = "that the car";
const char text_251[] PROGMEM = "isn't quite";
const char text_252[] PROGMEM = "complete.";
const char text_253[] PROGMEM = "What should you";
const char text_254[] PROGMEM = "do?";
const char text_255[] PROGMEM = "1. Check what";
const char text_256[] PROGMEM = "parts are";
const char text_257[] PROGMEM = "missing.";
const char text_258[] PROGMEM = "2. Release the";
const char text_259[] PROGMEM = "handbrake.";
const char text_260[] PROGMEM = "3. Get out of";
const char text_261[] PROGMEM = "the car.";
const char text_262[] PROGMEM = "Despite knowing"; //areaInsideCarOpt2
const char text_263[] PROGMEM = "that the car is";
const char text_264[] PROGMEM = "incomplete, you";
const char text_265[] PROGMEM = "release the";
const char text_266[] PROGMEM = "handbrake.";
const char text_267[] PROGMEM = "The car begins";
const char text_268[] PROGMEM = "to roll, and";
const char text_269[] PROGMEM = "quickly";
const char text_270[] PROGMEM = "picks up speed.";
const char text_271[] PROGMEM = "Suddenly you";
const char text_272[] PROGMEM = "feel";
const char text_273[] PROGMEM = "weightless as";
const char text_274[] PROGMEM = "the ground";
const char text_275[] PROGMEM = "vanishes and a";
const char text_276[] PROGMEM = "pretty looking";
const char text_277[] PROGMEM = "valley is";
const char text_278[] PROGMEM = "hundreds of";
const char text_279[] PROGMEM = "meters below.";
const char text_280[] PROGMEM = "Press any";
const char text_281[] PROGMEM = "button to";
const char text_282[] PROGMEM = "continue.";
const char text_283[] PROGMEM = "The following"; //areaCarParts
const char text_284[] PROGMEM = "parts are";
const char text_285[] PROGMEM = "missing...";
const char text_286[] PROGMEM = "1. Check";
const char text_287[] PROGMEM = "pockets for";
const char text_288[] PROGMEM = "parts.";
const char text_289[] PROGMEM = "2. Forget about";
const char text_290[] PROGMEM = "parts for now.";
const char text_291[] PROGMEM = "The car is"; //areaCarParts_comp
const char text_292[] PROGMEM = "complete!";
const char text_293[] PROGMEM = "Press any";
const char text_294[] PROGMEM = "button to";
const char text_295[] PROGMEM = "continue.";
const char text_296[] PROGMEM = "You rummage"; //areaCarPartsPockets
const char text_297[] PROGMEM = "through your";
const char text_298[] PROGMEM = "pockets but";
const char text_299[] PROGMEM = "don't find any";
const char text_300[] PROGMEM = "of the required";
const char text_301[] PROGMEM = "parts.";
const char text_302[] PROGMEM = "Press any";
const char text_303[] PROGMEM = "button to";
const char text_304[] PROGMEM = "continue.";
const char text_305[] PROGMEM = "You are sitting"; //areaInsideCompleteCar
const char text_306[] PROGMEM = "comfortably in";
const char text_307[] PROGMEM = "the";
const char text_308[] PROGMEM = "driving seat.";
const char text_309[] PROGMEM = "The car is";
const char text_310[] PROGMEM = "complete! You";
const char text_311[] PROGMEM = "feel a sense of";
const char text_312[] PROGMEM = "accomplishment";
const char text_313[] PROGMEM = "as";
const char text_314[] PROGMEM = "you put your";
const char text_315[] PROGMEM = "seatbelt on.";
const char text_316[] PROGMEM = "What should you";
const char text_317[] PROGMEM = "do?";
const char text_318[] PROGMEM = "1. Drive the";
const char text_319[] PROGMEM = "car.";
const char text_320[] PROGMEM = "2. Get out of";
const char text_321[] PROGMEM = "the car.";
const char text_322[] PROGMEM = "You start up"; //areaInsideCompleteCarOpt1
const char text_323[] PROGMEM = "the car and";
const char text_324[] PROGMEM = "turn the stereo";
const char text_325[] PROGMEM = "on. The radio";
const char text_326[] PROGMEM = "is just static,";
const char text_327[] PROGMEM = "and there";
const char text_328[] PROGMEM = "is no CD in the";
const char text_329[] PROGMEM = "slot.";
const char text_330[] PROGMEM = "There's no way";
const char text_331[] PROGMEM = "you're going";
const char text_332[] PROGMEM = "anywhere";
const char text_333[] PROGMEM = "unless you have";
const char text_334[] PROGMEM = "some music to";
const char text_335[] PROGMEM = "listen to.";
const char text_336[] PROGMEM = "Press any";
const char text_337[] PROGMEM = "button to";
const char text_338[] PROGMEM = "continue.";
const char text_339[] PROGMEM = "You start up"; //areaInsideCompleteCarOpt1_CD
const char text_340[] PROGMEM = "the car and pop";
const char text_341[] PROGMEM = "your CD in.";
const char text_342[] PROGMEM = "Singing along";
const char text_343[] PROGMEM = "to Elton John,";
const char text_344[] PROGMEM = "you drive";
const char text_345[] PROGMEM = "away from the";
const char text_346[] PROGMEM = "cottage, down a";
const char text_347[] PROGMEM = "few";
const char text_348[] PROGMEM = "country lanes,";
const char text_349[] PROGMEM = "and then join";
const char text_350[] PROGMEM = "the A66";
const char text_351[] PROGMEM = "towards Scotch";
const char text_352[] PROGMEM = "corner.";
const char text_353[] PROGMEM = "Woop! You're on";
const char text_354[] PROGMEM = "your way home!";
const char text_355[] PROGMEM = "Press any";
const char text_356[] PROGMEM = "button to";
const char text_357[] PROGMEM = "continue.";
const char text_358[] PROGMEM = "Before you is a"; //areaCottage
const char text_359[] PROGMEM = "pretty white";
const char text_360[] PROGMEM = "cottage.";
const char text_361[] PROGMEM = "It looks like";
const char text_362[] PROGMEM = "no one has";
const char text_363[] PROGMEM = "lived here in";
const char text_364[] PROGMEM = "quite a long";
const char text_365[] PROGMEM = "time.";
const char text_366[] PROGMEM = "What should you";
const char text_367[] PROGMEM = "do?";
const char text_368[] PROGMEM = "1. Go back to";
const char text_369[] PROGMEM = "the car.";
const char text_370[] PROGMEM = "2. Enter the";
const char text_371[] PROGMEM = "cottage.";
const char text_372[] PROGMEM = "3. Visit the";
const char text_373[] PROGMEM = "outhouse.";
const char text_374[] PROGMEM = "4. Walk to the";
const char text_375[] PROGMEM = "garden.";
const char text_376[] PROGMEM = "The door creaks"; //areaCottageOpt2
const char text_377[] PROGMEM = "ominously as";
const char text_378[] PROGMEM = "you gently";
const char text_379[] PROGMEM = "push it open.";
const char text_380[] PROGMEM = "Press any";
const char text_381[] PROGMEM = "button to";
const char text_382[] PROGMEM = "continue.";
const char text_383[] PROGMEM = "The cottage"; //areaInsideCottage
const char text_384[] PROGMEM = "appears to be";
const char text_385[] PROGMEM = "an empty";
const char text_386[] PROGMEM = "holiday home.";
const char text_387[] PROGMEM = "There is a cute";
const char text_388[] PROGMEM = "cat in the";
const char text_389[] PROGMEM = "corner playing";
const char text_390[] PROGMEM = "with some keys,";
const char text_391[] PROGMEM = "and a CD";
const char text_392[] PROGMEM = "player sits on";
const char text_393[] PROGMEM = "the kitchen";
const char text_394[] PROGMEM = "table.";
const char text_395[] PROGMEM = "What should you";
const char text_396[] PROGMEM = "do?";
const char text_397[] PROGMEM = "1. Retrieve the";
const char text_398[] PROGMEM = "keys from the";
const char text_399[] PROGMEM = "cat.";
const char text_400[] PROGMEM = "2. Remove the";
const char text_401[] PROGMEM = "CD from the CD";
const char text_402[] PROGMEM = "player.";
const char text_403[] PROGMEM = "3. Leave the";
const char text_404[] PROGMEM = "cottage.";
const char text_405[] PROGMEM = "The cottage"; //areaInsideCottage_keys
const char text_406[] PROGMEM = "appears to be";
const char text_407[] PROGMEM = "an empty";
const char text_408[] PROGMEM = "holiday home.";
const char text_409[] PROGMEM = "There is a cute";
const char text_410[] PROGMEM = "cat in the";
const char text_411[] PROGMEM = "corner playing";
const char text_412[] PROGMEM = "with a mouse,";
const char text_413[] PROGMEM = "and a CD";
const char text_414[] PROGMEM = "player sits on";
const char text_415[] PROGMEM = "the kitchen";
const char text_416[] PROGMEM = "table.";
const char text_417[] PROGMEM = "What should you";
const char text_418[] PROGMEM = "do?";
const char text_419[] PROGMEM = "1. Stroke the";
const char text_420[] PROGMEM = "cat.";
const char text_421[] PROGMEM = "2. Remove the";
const char text_422[] PROGMEM = "CD from the CD";
const char text_423[] PROGMEM = "player.";
const char text_424[] PROGMEM = "3. Leave the";
const char text_425[] PROGMEM = "cottage.";
const char text_426[] PROGMEM = "The cottage"; //areaInsideCottage_cd
const char text_427[] PROGMEM = "appears to be";
const char text_428[] PROGMEM = "an empty";
const char text_429[] PROGMEM = "holiday home.";
const char text_430[] PROGMEM = "There is a cute";
const char text_431[] PROGMEM = "cat in the";
const char text_432[] PROGMEM = "corner playing";
const char text_433[] PROGMEM = "with a mouse,";
const char text_434[] PROGMEM = "and a CD";
const char text_435[] PROGMEM = "player sits on";
const char text_436[] PROGMEM = "the kitchen";
const char text_437[] PROGMEM = "table.";
const char text_438[] PROGMEM = "What should you";
const char text_439[] PROGMEM = "do?";
const char text_440[] PROGMEM = "1. Stroke the";
const char text_441[] PROGMEM = "cat.";
const char text_442[] PROGMEM = "2. Press play";
const char text_443[] PROGMEM = "on the CD";
const char text_444[] PROGMEM = "player.";
const char text_445[] PROGMEM = "3. Leave the";
const char text_446[] PROGMEM = "cottage.";
const char text_447[] PROGMEM = "You try to coax"; //areaInsideCottageOpt1
const char text_448[] PROGMEM = "the cat to let";
const char text_449[] PROGMEM = "you have";
const char text_450[] PROGMEM = "the keys, but";
const char text_451[] PROGMEM = "it just keeps";
const char text_452[] PROGMEM = "meowing and";
const char text_453[] PROGMEM = "trying to claw";
const char text_454[] PROGMEM = "you.";
const char text_455[] PROGMEM = "It's a shame";
const char text_456[] PROGMEM = "you don't have";
const char text_457[] PROGMEM = "anything it";
const char text_458[] PROGMEM = "could play with";
const char text_459[] PROGMEM = "instead.";
const char text_460[] PROGMEM = "Press any";
const char text_461[] PROGMEM = "button to";
const char text_462[] PROGMEM = "continue.";
const char text_463[] PROGMEM = "You take the"; //areaInsideCottageOpt1_mouse
const char text_464[] PROGMEM = "dead mouse out";
const char text_465[] PROGMEM = "from your";
const char text_466[] PROGMEM = "pocket and";
const char text_467[] PROGMEM = "wiggle it at";
const char text_468[] PROGMEM = "the cat. It";
const char text_469[] PROGMEM = "leaves the keys";
const char text_470[] PROGMEM = "unguarded on";
const char text_471[] PROGMEM = "the floor,";
const char text_472[] PROGMEM = "and it comes to";
const char text_473[] PROGMEM = "play with the";
const char text_474[] PROGMEM = "mouse.";
const char text_475[] PROGMEM = "You quickly";
const char text_476[] PROGMEM = "pocket the";
const char text_477[] PROGMEM = "keys.";
const char text_478[] PROGMEM = "Press any";
const char text_479[] PROGMEM = "button to";
const char text_480[] PROGMEM = "continue.";
const char text_481[] PROGMEM = "The cat purrs"; //areaInsideCottageOpt1_stroke
const char text_482[] PROGMEM = "as you gently";
const char text_483[] PROGMEM = "stroke it.";
const char text_484[] PROGMEM = "She seems to";
const char text_485[] PROGMEM = "like you.";
const char text_486[] PROGMEM = "Press any";
const char text_487[] PROGMEM = "button to";
const char text_488[] PROGMEM = "continue.";
const char text_489[] PROGMEM = "You inspect the"; //areaInsideCottageOpt2
const char text_490[] PROGMEM = "CD player. It's";
const char text_491[] PROGMEM = "plugged";
const char text_492[] PROGMEM = "in with an";
const char text_493[] PROGMEM = "Elton John CD";
const char text_494[] PROGMEM = "inside. A";
const char text_495[] PROGMEM = "BabyMetal CD is";
const char text_496[] PROGMEM = "next to it on";
const char text_497[] PROGMEM = "the table.";
const char text_498[] PROGMEM = "You think it's";
const char text_499[] PROGMEM = "best not to";
const char text_500[] PROGMEM = "disturb it";
const char text_501[] PROGMEM = "at the moment.";
const char text_502[] PROGMEM = "Press any";
const char text_503[] PROGMEM = "button to";
const char text_504[] PROGMEM = "continue.";
const char text_505[] PROGMEM = "You inspect the"; //areaInsideCottageOpt2_takeCD
const char text_506[] PROGMEM = "CD player. It's";
const char text_507[] PROGMEM = "plugged";
const char text_508[] PROGMEM = "in with an";
const char text_509[] PROGMEM = "Elton John CD";
const char text_510[] PROGMEM = "inside. A";
const char text_511[] PROGMEM = "BabyMetal CD is";
const char text_512[] PROGMEM = "next to it on";
const char text_513[] PROGMEM = "the table.";
const char text_514[] PROGMEM = "You take the";
const char text_515[] PROGMEM = "Elton John CD";
const char text_516[] PROGMEM = "and put it";
const char text_517[] PROGMEM = "in your pocket.";
const char text_518[] PROGMEM = "You pop the";
const char text_519[] PROGMEM = "BabyMetal CD";
const char text_520[] PROGMEM = "into the";
const char text_521[] PROGMEM = "player.";
const char text_522[] PROGMEM = "Press any";
const char text_523[] PROGMEM = "button to";
const char text_524[] PROGMEM = "continue.";
const char text_525[] PROGMEM = "You inspect the"; //areaInsideCottageOpt2_play
const char text_526[] PROGMEM = "CD player. It's";
const char text_527[] PROGMEM = "plugged";
const char text_528[] PROGMEM = "in with a";
const char text_529[] PROGMEM = "BabyMetal CD";
const char text_530[] PROGMEM = "inside. You";
const char text_531[] PROGMEM = "press";
const char text_532[] PROGMEM = "play and do a";
const char text_533[] PROGMEM = "little dance";
const char text_534[] PROGMEM = "around the";
const char text_535[] PROGMEM = "cottage whilst";
const char text_536[] PROGMEM = "singing along";
const char text_537[] PROGMEM = "to 'Gimme";
const char text_538[] PROGMEM = "Chocolate!!'.";
const char text_539[] PROGMEM = "Oh yeah!";
const char text_540[] PROGMEM = "Press any";
const char text_541[] PROGMEM = "button to";
const char text_542[] PROGMEM = "continue.";
const char text_543[] PROGMEM = "In the"; //areaGarden
const char text_544[] PROGMEM = "beautiful";
const char text_545[] PROGMEM = "cottage garden";
const char text_546[] PROGMEM = "there is";
const char text_547[] PROGMEM = "an old wooden";
const char text_548[] PROGMEM = "shed, a small";
const char text_549[] PROGMEM = "well, and an";
const char text_550[] PROGMEM = "outhouse";
const char text_551[] PROGMEM = "toilet. You can";
const char text_552[] PROGMEM = "see the beach.";
const char text_553[] PROGMEM = "What should you";
const char text_554[] PROGMEM = "do?";
const char text_555[] PROGMEM = "1. Walk up to";
const char text_556[] PROGMEM = "the pretty";
const char text_557[] PROGMEM = "cottage.";
const char text_558[] PROGMEM = "2. Look inside";
const char text_559[] PROGMEM = "of the old";
const char text_560[] PROGMEM = "shed.";
const char text_561[] PROGMEM = "3. Investigate";
const char text_562[] PROGMEM = "the well.";
const char text_563[] PROGMEM = "4. Walk down to";
const char text_564[] PROGMEM = "the beach.";
const char text_565[] PROGMEM = "You take a"; //areaGardenOpt4
const char text_566[] PROGMEM = "leisurely";
const char text_567[] PROGMEM = "stroll down";
const char text_568[] PROGMEM = "towards";
const char text_569[] PROGMEM = "the beach. It's";
const char text_570[] PROGMEM = "a nice day and";
const char text_571[] PROGMEM = "there are";
const char text_572[] PROGMEM = "butterflies";
const char text_573[] PROGMEM = "flirting with";
const char text_574[] PROGMEM = "the flowers";
const char text_575[] PROGMEM = "growing at the";
const char text_576[] PROGMEM = "sides of the";
const char text_577[] PROGMEM = "path.";
const char text_578[] PROGMEM = "The beach looks";
const char text_579[] PROGMEM = "like something";
const char text_580[] PROGMEM = "described";
const char text_581[] PROGMEM = "in a text-based";
const char text_582[] PROGMEM = "adventure as";
const char text_583[] PROGMEM = "you";
const char text_584[] PROGMEM = "approach.";
const char text_585[] PROGMEM = "Press any";
const char text_586[] PROGMEM = "button to";
const char text_587[] PROGMEM = "continue.";
const char text_588[] PROGMEM = "Inside the shed"; //areaShed
const char text_589[] PROGMEM = "there is a few";
const char text_590[] PROGMEM = "empty";
const char text_591[] PROGMEM = "petrol cans, a";
const char text_592[] PROGMEM = "bottle marked";
const char text_593[] PROGMEM = "with skull";
const char text_594[] PROGMEM = "& crossbones,";
const char text_595[] PROGMEM = "and an orange";
const char text_596[] PROGMEM = "frisbee.";
const char text_597[] PROGMEM = "What should you";
const char text_598[] PROGMEM = "do?";
const char text_599[] PROGMEM = "1. Pick up an";
const char text_600[] PROGMEM = "empty petrol";
const char text_601[] PROGMEM = "can.";
const char text_602[] PROGMEM = "2. Drink the";
const char text_603[] PROGMEM = "contents of the";
const char text_604[] PROGMEM = "bottle.";
const char text_605[] PROGMEM = "3. Leave the";
const char text_606[] PROGMEM = "shed and close";
const char text_607[] PROGMEM = "the door.";
const char text_608[] PROGMEM = "4. Pick up the";
const char text_609[] PROGMEM = "frisbee.";
const char text_610[] PROGMEM = "Inside the shed"; //areaShed_frisbee
const char text_611[] PROGMEM = "there is a few";
const char text_612[] PROGMEM = "empty";
const char text_613[] PROGMEM = "petrol cans and";
const char text_614[] PROGMEM = "a bottle marked";
const char text_615[] PROGMEM = "with";
const char text_616[] PROGMEM = "skull &";
const char text_617[] PROGMEM = "crossbones.";
const char text_618[] PROGMEM = "What should you";
const char text_619[] PROGMEM = "do?";
const char text_620[] PROGMEM = "1. Pick up an";
const char text_621[] PROGMEM = "empty petrol";
const char text_622[] PROGMEM = "can.";
const char text_623[] PROGMEM = "2. Drink the";
const char text_624[] PROGMEM = "contents of the";
const char text_625[] PROGMEM = "bottle.";
const char text_626[] PROGMEM = "3. Leave the";
const char text_627[] PROGMEM = "shed and close";
const char text_628[] PROGMEM = "the door.";
const char text_629[] PROGMEM = "There isn't"; //areaShedOpt1
const char text_630[] PROGMEM = "much point in";
const char text_631[] PROGMEM = "an empty can,";
const char text_632[] PROGMEM = "and you can't";
const char text_633[] PROGMEM = "see any petrol";
const char text_634[] PROGMEM = "nearby.";
const char text_635[] PROGMEM = "You decide to";
const char text_636[] PROGMEM = "just leave the";
const char text_637[] PROGMEM = "cans where";
const char text_638[] PROGMEM = "they are.";
const char text_639[] PROGMEM = "Press any";
const char text_640[] PROGMEM = "button to";
const char text_641[] PROGMEM = "continue.";
const char text_642[] PROGMEM = "You pick up one"; //areaShedOpt1_can
const char text_643[] PROGMEM = "of the empty";
const char text_644[] PROGMEM = "cans";
const char text_645[] PROGMEM = "thinking that";
const char text_646[] PROGMEM = "it will";
const char text_647[] PROGMEM = "probably come";
const char text_648[] PROGMEM = "in";
const char text_649[] PROGMEM = "handy.";
const char text_650[] PROGMEM = "Press any";
const char text_651[] PROGMEM = "button to";
const char text_652[] PROGMEM = "continue.";
const char text_653[] PROGMEM = "You don't need"; //areaShedOpt1_got
const char text_654[] PROGMEM = "any more empty";
const char text_655[] PROGMEM = "petrol";
const char text_656[] PROGMEM = "cans. Besides,";
const char text_657[] PROGMEM = "it looks like";
const char text_658[] PROGMEM = "there is a";
const char text_659[] PROGMEM = "family of";
const char text_660[] PROGMEM = "little mice";
const char text_661[] PROGMEM = "living in one";
const char text_662[] PROGMEM = "of";
const char text_663[] PROGMEM = "them.";
const char text_664[] PROGMEM = "Press any";
const char text_665[] PROGMEM = "button to";
const char text_666[] PROGMEM = "continue.";
const char text_667[] PROGMEM = "You cheerfully"; //areaShedOpt2
const char text_668[] PROGMEM = "pop the cork on";
const char text_669[] PROGMEM = "the small";
const char text_670[] PROGMEM = "bottle and down";
const char text_671[] PROGMEM = "the contents in";
const char text_672[] PROGMEM = "one go.";
const char text_673[] PROGMEM = "Nothing";
const char text_674[] PROGMEM = "happens.";
const char text_675[] PROGMEM = "Oh wait...";
const char text_676[] PROGMEM = "Press any";
const char text_677[] PROGMEM = "button to";
const char text_678[] PROGMEM = "continue.";
const char text_679[] PROGMEM = "Everyone loves"; //areaShedOpt4
const char text_680[] PROGMEM = "playing with";
const char text_681[] PROGMEM = "frisbees!";
const char text_682[] PROGMEM = "You pick up the";
const char text_683[] PROGMEM = "frisbee and";
const char text_684[] PROGMEM = "stick it up";
const char text_685[] PROGMEM = "your jumper.";
const char text_686[] PROGMEM = "Press any";
const char text_687[] PROGMEM = "button to";
const char text_688[] PROGMEM = "continue.";
const char text_689[] PROGMEM = "Looking down"; //areaWell
const char text_690[] PROGMEM = "the well, you";
const char text_691[] PROGMEM = "see something";
const char text_692[] PROGMEM = "reflective at";
const char text_693[] PROGMEM = "the bottom. The";
const char text_694[] PROGMEM = "outhouse";
const char text_695[] PROGMEM = "toilet and old";
const char text_696[] PROGMEM = "shed are";
const char text_697[] PROGMEM = "nearby.";
const char text_698[] PROGMEM = "What should you";
const char text_699[] PROGMEM = "do?";
const char text_700[] PROGMEM = "1. Retrieve";
const char text_701[] PROGMEM = "item from the";
const char text_702[] PROGMEM = "well.";
const char text_703[] PROGMEM = "2. Look inside";
const char text_704[] PROGMEM = "the old shed.";
const char text_705[] PROGMEM = "3. Visit the";
const char text_706[] PROGMEM = "outhouse.";
const char text_707[] PROGMEM = "4. Head back to";
const char text_708[] PROGMEM = "the cottage.";
const char text_709[] PROGMEM = "Looking down"; //areaWell_mirror
const char text_710[] PROGMEM = "the well, there";
const char text_711[] PROGMEM = "is a few";
const char text_712[] PROGMEM = "shiny coins at";
const char text_713[] PROGMEM = "the bottom. The";
const char text_714[] PROGMEM = "outhouse";
const char text_715[] PROGMEM = "toilet and old";
const char text_716[] PROGMEM = "shed are";
const char text_717[] PROGMEM = "nearby.";
const char text_718[] PROGMEM = "What should you";
const char text_719[] PROGMEM = "do?";
const char text_720[] PROGMEM = "1. Toss a coin";
const char text_721[] PROGMEM = "in the well.";
const char text_722[] PROGMEM = "2. Look inside";
const char text_723[] PROGMEM = "the old shed.";
const char text_724[] PROGMEM = "3. Visit the";
const char text_725[] PROGMEM = "outhouse.";
const char text_726[] PROGMEM = "4. Head back to";
const char text_727[] PROGMEM = "the cottage.";
const char text_728[] PROGMEM = "You can't seem"; //areaWellOpt1
const char text_729[] PROGMEM = "to reach it,";
const char text_730[] PROGMEM = "it's a long";
const char text_731[] PROGMEM = "way down.";
const char text_732[] PROGMEM = "Press any";
const char text_733[] PROGMEM = "button to";
const char text_734[] PROGMEM = "continue.";
const char text_735[] PROGMEM = "You lower the"; //areaWellOpt1_rope
const char text_736[] PROGMEM = "rope down the";
const char text_737[] PROGMEM = "well,";
const char text_738[] PROGMEM = "however you";
const char text_739[] PROGMEM = "can't seem to";
const char text_740[] PROGMEM = "hook the rope";
const char text_741[] PROGMEM = "onto the item";
const char text_742[] PROGMEM = "so that you can";
const char text_743[] PROGMEM = "pull it";
const char text_744[] PROGMEM = "up to the";
const char text_745[] PROGMEM = "surface.";
const char text_746[] PROGMEM = "Perhaps you";
const char text_747[] PROGMEM = "need something";
const char text_748[] PROGMEM = "in addition";
const char text_749[] PROGMEM = "to the rope.";
const char text_750[] PROGMEM = "Press any";
const char text_751[] PROGMEM = "button to";
const char text_752[] PROGMEM = "continue.";
const char text_753[] PROGMEM = "You tie the"; //areaWellOpt1_hook
const char text_754[] PROGMEM = "hook to your";
const char text_755[] PROGMEM = "rope, and lower";
const char text_756[] PROGMEM = "it down the";
const char text_757[] PROGMEM = "well. After";
const char text_758[] PROGMEM = "some time and";
const char text_759[] PROGMEM = "cursing you";
const char text_760[] PROGMEM = "manage to hook";
const char text_761[] PROGMEM = "onto the item";
const char text_762[] PROGMEM = "and pull it out";
const char text_763[] PROGMEM = "of the well.";
const char text_764[] PROGMEM = "It's a car";
const char text_765[] PROGMEM = "rear-view";
const char text_766[] PROGMEM = "mirror, you pop";
const char text_767[] PROGMEM = "it";
const char text_768[] PROGMEM = "in your pocket.";
const char text_769[] PROGMEM = "Press any";
const char text_770[] PROGMEM = "button to";
const char text_771[] PROGMEM = "continue.";
const char text_772[] PROGMEM = "You make a wish"; //areaWellOpt1_coin
const char text_773[] PROGMEM = "as you throw a";
const char text_774[] PROGMEM = "coin into";
const char text_775[] PROGMEM = "the well.";
const char text_776[] PROGMEM = "You wish that";
const char text_777[] PROGMEM = "you had a pet";
const char text_778[] PROGMEM = "unicorn with";
const char text_779[] PROGMEM = "rainbow hair.";
const char text_780[] PROGMEM = "Press any";
const char text_781[] PROGMEM = "button to";
const char text_782[] PROGMEM = "continue.";
const char text_783[] PROGMEM = "You are in the"; //areaOuthouse
const char text_784[] PROGMEM = "outhouse.";
const char text_785[] PROGMEM = "Nothing else is";
const char text_786[] PROGMEM = "here but a";
const char text_787[] PROGMEM = "toilet. It's";
const char text_788[] PROGMEM = "quite dirty and";
const char text_789[] PROGMEM = "there appears";
const char text_790[] PROGMEM = "to be a large";
const char text_791[] PROGMEM = "fishing hook";
const char text_792[] PROGMEM = "at the bottom";
const char text_793[] PROGMEM = "of the toilet";
const char text_794[] PROGMEM = "bowl.";
const char text_795[] PROGMEM = "What should you";
const char text_796[] PROGMEM = "do?";
const char text_797[] PROGMEM = "1. Walk back to";
const char text_798[] PROGMEM = "the cottage.";
const char text_799[] PROGMEM = "2. Go to the";
const char text_800[] PROGMEM = "well.";
const char text_801[] PROGMEM = "3. Retrieve the";
const char text_802[] PROGMEM = "hook from the";
const char text_803[] PROGMEM = "toilet.";
const char text_804[] PROGMEM = "You are in the"; //areaOuthouse_hook
const char text_805[] PROGMEM = "outhouse.";
const char text_806[] PROGMEM = "Nothing else is";
const char text_807[] PROGMEM = "here but a";
const char text_808[] PROGMEM = "toilet. Thanks";
const char text_809[] PROGMEM = "to your recent";
const char text_810[] PROGMEM = "cleaning spree,";
const char text_811[] PROGMEM = "it appears to";
const char text_812[] PROGMEM = "be";
const char text_813[] PROGMEM = "spotlessly";
const char text_814[] PROGMEM = "clean.";
const char text_815[] PROGMEM = "What should you";
const char text_816[] PROGMEM = "do?";
const char text_817[] PROGMEM = "1. Walk back to";
const char text_818[] PROGMEM = "the cottage.";
const char text_819[] PROGMEM = "2. Go to the";
const char text_820[] PROGMEM = "well.";
const char text_821[] PROGMEM = "3. Use the";
const char text_822[] PROGMEM = "toilet.";
const char text_823[] PROGMEM = "You decide that"; //areaOuthouseOpt3
const char text_824[] PROGMEM = "there's no way";
const char text_825[] PROGMEM = "you are";
const char text_826[] PROGMEM = "going to put";
const char text_827[] PROGMEM = "your hand in";
const char text_828[] PROGMEM = "there just to";
const char text_829[] PROGMEM = "obtain a hook";
const char text_830[] PROGMEM = "that you have";
const char text_831[] PROGMEM = "no use for!";
const char text_832[] PROGMEM = "Press any";
const char text_833[] PROGMEM = "button to";
const char text_834[] PROGMEM = "continue.";
const char text_835[] PROGMEM = "Holding your"; //areaOuthouseOpt3_hook
const char text_836[] PROGMEM = "breath and";
const char text_837[] PROGMEM = "looking away,";
const char text_838[] PROGMEM = "you slowly dip";
const char text_839[] PROGMEM = "your hand into";
const char text_840[] PROGMEM = "the toilet";
const char text_841[] PROGMEM = "bowl. The water";
const char text_842[] PROGMEM = "is cold and";
const char text_843[] PROGMEM = "slimy. You";
const char text_844[] PROGMEM = "manage to";
const char text_845[] PROGMEM = "retrieve the";
const char text_846[] PROGMEM = "hook.";
const char text_847[] PROGMEM = "Disguisted, you";
const char text_848[] PROGMEM = "fetch some";
const char text_849[] PROGMEM = "cleaning";
const char text_850[] PROGMEM = "products from";
const char text_851[] PROGMEM = "the cottage and";
const char text_852[] PROGMEM = "give the";
const char text_853[] PROGMEM = "toilet a good";
const char text_854[] PROGMEM = "scrub.";
const char text_855[] PROGMEM = "Press any";
const char text_856[] PROGMEM = "button to";
const char text_857[] PROGMEM = "continue.";
const char text_858[] PROGMEM = "You have a wee."; //areaOuthouseOpt3_wee
const char text_859[] PROGMEM = "Ahh that's much";
const char text_860[] PROGMEM = "better!";
const char text_861[] PROGMEM = "Press any";
const char text_862[] PROGMEM = "button to";
const char text_863[] PROGMEM = "continue.";
const char text_864[] PROGMEM = "A boat is"; //areaBeach
const char text_865[] PROGMEM = "resting on the";
const char text_866[] PROGMEM = "beach, out of";
const char text_867[] PROGMEM = "the water. You";
const char text_868[] PROGMEM = "can see the";
const char text_869[] PROGMEM = "path leading";
const char text_870[] PROGMEM = "up towards the";
const char text_871[] PROGMEM = "cottage. You";
const char text_872[] PROGMEM = "spot a snail";
const char text_873[] PROGMEM = "shell poking";
const char text_874[] PROGMEM = "out of the";
const char text_875[] PROGMEM = "sand.";
const char text_876[] PROGMEM = "What should you";
const char text_877[] PROGMEM = "do?";
const char text_878[] PROGMEM = "1. Investigate";
const char text_879[] PROGMEM = "the boat.";
const char text_880[] PROGMEM = "2. Head back up";
const char text_881[] PROGMEM = "to the cottage";
const char text_882[] PROGMEM = "garden.";
const char text_883[] PROGMEM = "3. Pick up the";
const char text_884[] PROGMEM = "snail.";
const char text_885[] PROGMEM = "A boat is";//areaBeach_snail
const char text_886[] PROGMEM = "resting on the";
const char text_887[] PROGMEM = "beach, out of";
const char text_888[] PROGMEM = "the water. You";
const char text_889[] PROGMEM = "can see the";
const char text_890[] PROGMEM = "path leading";
const char text_891[] PROGMEM = "up towards the";
const char text_892[] PROGMEM = "cottage. You";
const char text_893[] PROGMEM = "can't spot";
const char text_894[] PROGMEM = "any snails";
const char text_895[] PROGMEM = "anywhere.";
const char text_896[] PROGMEM = "What should you";
const char text_897[] PROGMEM = "do?";
const char text_898[] PROGMEM = "1. Investigate";
const char text_899[] PROGMEM = "the boat.";
const char text_900[] PROGMEM = "2. Head back up";
const char text_901[] PROGMEM = "to the cottage";
const char text_902[] PROGMEM = "garden.";
const char text_903[] PROGMEM = "3. Search for";
const char text_904[] PROGMEM = "snails.";
const char text_905[] PROGMEM = "As you bend";//areaBeachOpt3
const char text_906[] PROGMEM = "down to pick up";
const char text_907[] PROGMEM = "the snail,";
const char text_908[] PROGMEM = "you realise it";
const char text_909[] PROGMEM = "isn't a snail";
const char text_910[] PROGMEM = "at all!";
const char text_911[] PROGMEM = "It's the round";
const char text_912[] PROGMEM = "plastic knob of";
const char text_913[] PROGMEM = "a car";
const char text_914[] PROGMEM = "window winder.";
const char text_915[] PROGMEM = "You pull the";
const char text_916[] PROGMEM = "winder out";
const char text_917[] PROGMEM = "from under the";
const char text_918[] PROGMEM = "sand, dust it";
const char text_919[] PROGMEM = "off and pop";
const char text_920[] PROGMEM = "it in your";
const char text_921[] PROGMEM = "pocket.";
const char text_922[] PROGMEM = "Press any";
const char text_923[] PROGMEM = "button to";
const char text_924[] PROGMEM = "continue.";
const char text_925[] PROGMEM = "You walk up and"; //areaBeachOpt3_search
const char text_926[] PROGMEM = "down the beach";
const char text_927[] PROGMEM = "for a bit";
const char text_928[] PROGMEM = "searching for";
const char text_929[] PROGMEM = "sea snails.";
const char text_930[] PROGMEM = "You find one";
const char text_931[] PROGMEM = "and put him in";
const char text_932[] PROGMEM = "the sea. He";
const char text_933[] PROGMEM = "looks much";
const char text_934[] PROGMEM = "happier now.";
const char text_935[] PROGMEM = "Press any";
const char text_936[] PROGMEM = "button to";
const char text_937[] PROGMEM = "continue.";
const char text_938[] PROGMEM = "Inside the"; //areaBoat
const char text_939[] PROGMEM = "small boat,";
const char text_940[] PROGMEM = "there are a few";
const char text_941[] PROGMEM = "coils of rope";
const char text_942[] PROGMEM = "and an outboard";
const char text_943[] PROGMEM = "engine.";
const char text_944[] PROGMEM = "It looks";
const char text_945[] PROGMEM = "seaworthy.";
const char text_946[] PROGMEM = "What should you";
const char text_947[] PROGMEM = "do?";
const char text_948[] PROGMEM = "1. Start the";
const char text_949[] PROGMEM = "boat up and";
const char text_950[] PROGMEM = "sail away.";
const char text_951[] PROGMEM = "2. Take petrol";
const char text_952[] PROGMEM = "from the engine";
const char text_953[] PROGMEM = "tank.";
const char text_954[] PROGMEM = "3. Take a coil";
const char text_955[] PROGMEM = "of rope.";
const char text_956[] PROGMEM = "4. Leave the";
const char text_957[] PROGMEM = "boat.";
const char text_958[] PROGMEM = "Although the"; //areaBoatOpt1
const char text_959[] PROGMEM = "boat is";
const char text_960[] PROGMEM = "certainly";
const char text_961[] PROGMEM = "seaworthy";
const char text_962[] PROGMEM = "and there is";
const char text_963[] PROGMEM = "plenty of fuel,";
const char text_964[] PROGMEM = "you have no";
const char text_965[] PROGMEM = "compass and";
const char text_966[] PROGMEM = "would most";
const char text_967[] PROGMEM = "definitely get";
const char text_968[] PROGMEM = "lost at sea.";
const char text_969[] PROGMEM = "Besides you";
const char text_970[] PROGMEM = "haven't packed";
const char text_971[] PROGMEM = "any lunch.";
const char text_972[] PROGMEM = "Press any";
const char text_973[] PROGMEM = "button to";
const char text_974[] PROGMEM = "continue.";
const char text_975[] PROGMEM = "Unfortunately,"; //areaBoatOpt2
const char text_976[] PROGMEM = "you don't have";
const char text_977[] PROGMEM = "anything";
const char text_978[] PROGMEM = "to carry the";
const char text_979[] PROGMEM = "petrol in, so";
const char text_980[] PROGMEM = "you leave it";
const char text_981[] PROGMEM = "alone for now.";
const char text_982[] PROGMEM = "Press any";
const char text_983[] PROGMEM = "button to";
const char text_984[] PROGMEM = "continue.";
const char text_985[] PROGMEM = "You pour the"; //areaBoatOpt2_can
const char text_986[] PROGMEM = "petrol into";
const char text_987[] PROGMEM = "your empty can";
const char text_988[] PROGMEM = "until it's";
const char text_989[] PROGMEM = "full.";
const char text_990[] PROGMEM = "Press any";
const char text_991[] PROGMEM = "button to";
const char text_992[] PROGMEM = "continue.";
const char text_993[] PROGMEM = "You don't need"; //areaBoatOpt2_dneed
const char text_994[] PROGMEM = "any more";
const char text_995[] PROGMEM = "petrol.";
const char text_996[] PROGMEM = "Press any";
const char text_997[] PROGMEM = "button to";
const char text_998[] PROGMEM = "continue.";
const char text_999[] PROGMEM = "The rope is of"; //areaBoatOpt3
const char text_1000[] PROGMEM = "a good quality,";
const char text_1001[] PROGMEM = "both thin";
const char text_1002[] PROGMEM = "and strong. You";
const char text_1003[] PROGMEM = "pick up a coil";
const char text_1004[] PROGMEM = "and carry";
const char text_1005[] PROGMEM = "it over your";
const char text_1006[] PROGMEM = "shoulder.";
const char text_1007[] PROGMEM = "Press any";
const char text_1008[] PROGMEM = "button to";
const char text_1009[] PROGMEM = "continue.";
const char text_1010[] PROGMEM = "You decide that"; //areaBoatOpt3_dneed
const char text_1011[] PROGMEM = "you don't need";
const char text_1012[] PROGMEM = "any more";
const char text_1013[] PROGMEM = "rope.";
const char text_1014[] PROGMEM = "Press any";
const char text_1015[] PROGMEM = "button to";
const char text_1016[] PROGMEM = "continue.";
const char text_1017[] PROGMEM = "Congratulations!";  //areaFinish
const char text_1018[] PROGMEM = "";
const char text_1019[] PROGMEM = "";
const char text_1020[] PROGMEM = "      The"; //areaCredits
const char text_1021[] PROGMEM = " Lonely Cottage";
const char text_1022[] PROGMEM = "  A text based";
const char text_1023[] PROGMEM = "  multi-choice";
const char text_1024[] PROGMEM = "   adventure";
const char text_1025[] PROGMEM = " Designed and";
const char text_1026[] PROGMEM = "  written by";
const char text_1027[] PROGMEM = "  W K Jones";
const char text_1028[] PROGMEM = "www.warmcat.uk";
const char text_1029[] PROGMEM = " Press select.";
const char text_1030[] PROGMEM = "    The"; //areaAmyCredits
const char text_1031[] PROGMEM = "Lonely Cottage  ";
const char text_1032[] PROGMEM = "  A text based";
const char text_1033[] PROGMEM = "multi-choice";
const char text_1034[] PROGMEM = "adventure";
const char text_1035[] PROGMEM = "   Written by";
const char text_1036[] PROGMEM = "Wayne Jones.";
const char text_1037[] PROGMEM = "Xmas 2014";
const char text_1038[] PROGMEM = "   Merry";
const char text_1039[] PROGMEM = "Christmas Amy!";
const char text_1040[] PROGMEM = "How to play:";//areaIntro
const char text_1041[] PROGMEM = "Use the four";
const char text_1042[] PROGMEM = "buttons to";
const char text_1043[] PROGMEM = "select from the";
const char text_1044[] PROGMEM = "possible";
const char text_1045[] PROGMEM = "choices. The";
const char text_1046[] PROGMEM = "aim of the game";
const char text_1047[] PROGMEM = "is";
const char text_1048[] PROGMEM = "to escape and";
const char text_1049[] PROGMEM = "make your way";
const char text_1050[] PROGMEM = "home.";
const char text_1051[] PROGMEM = "Good luck!";
const char text_1052[] PROGMEM = "Press a button";
const char text_1053[] PROGMEM = "to begin the";
const char text_1054[] PROGMEM = "adventure.";
const char text_1055[] PROGMEM = "Press any";
const char text_1056[] PROGMEM = "button to";
const char text_1057[] PROGMEM = "continue.";
PGM_P const text[] PROGMEM = {
text_0,
text_1,text_2,text_3,text_4,text_5,text_6,text_7,text_8,text_9,text_10,
text_11,text_12,text_13,text_14,text_15,text_16,text_17,text_18,text_19,text_20,
text_21,text_22,text_23,text_24,text_25,text_26,text_27,text_28,text_29,text_30,
text_31,text_32,text_33,text_34,text_35,text_36,text_37,text_38,text_39,text_40,
text_41,text_42,text_43,text_44,text_45,text_46,text_47,text_48,text_49,text_50,
text_51,text_52,text_53,text_54,text_55,text_56,text_57,text_58,text_59,text_60,
text_61,text_62,text_63,text_64,text_65,text_66,text_67,text_68,text_69,text_70,
text_71,text_72,text_73,text_74,text_75,text_76,text_77,text_78,text_79,text_80,
text_81,text_82,text_83,text_84,text_85,text_86,text_87,text_88,text_89,text_90,
text_91,text_92,text_93,text_94,text_95,text_96,text_97,text_98,text_99,text_100,
text_101,text_102,text_103,text_104,text_105,text_106,text_107,text_108,text_109,text_110,
text_111,text_112,text_113,text_114,text_115,text_116,text_117,text_118,text_119,text_120,
text_121,text_122,text_123,text_124,text_125,text_126,text_127,text_128,text_129,text_130,
text_131,text_132,text_133,text_134,text_135,text_136,text_137,text_138,text_139,text_140,
text_141,text_142,text_143,text_144,text_145,text_146,text_147,text_148,text_149,text_150,
text_151,text_152,text_153,text_154,text_155,text_156,text_157,text_158,text_159,text_160,
text_161,text_162,text_163,text_164,text_165,text_166,text_167,text_168,text_169,text_170,
text_171,text_172,text_173,text_174,text_175,text_176,text_177,text_178,text_179,text_180,
text_181,text_182,text_183,text_184,text_185,text_186,text_187,text_188,text_189,text_190,
text_191,text_192,text_193,text_194,text_195,text_196,text_197,text_198,text_199,text_200,
text_201,text_202,text_203,text_204,text_205,text_206,text_207,text_208,text_209,text_210,
text_211,text_212,text_213,text_214,text_215,text_216,text_217,text_218,text_219,text_220,
text_221,text_222,text_223,text_224,text_225,text_226,text_227,text_228,text_229,text_230,
text_231,text_232,text_233,text_234,text_235,text_236,text_237,text_238,text_239,text_240,
text_241,text_242,text_243,text_244,text_245,text_246,text_247,text_248,text_249,text_250,
text_251,text_252,text_253,text_254,text_255,text_256,text_257,text_258,text_259,text_260,
text_261,text_262,text_263,text_264,text_265,text_266,text_267,text_268,text_269,text_270,
text_271,text_272,text_273,text_274,text_275,text_276,text_277,text_278,text_279,text_280,
text_281,text_282,text_283,text_284,text_285,text_286,text_287,text_288,text_289,text_290,
text_291,text_292,text_293,text_294,text_295,text_296,text_297,text_298,text_299,text_300,
text_301,text_302,text_303,text_304,text_305,text_306,text_307,text_308,text_309,text_310,
text_311,text_312,text_313,text_314,text_315,text_316,text_317,text_318,text_319,text_320,
text_321,text_322,text_323,text_324,text_325,text_326,text_327,text_328,text_329,text_330,
text_331,text_332,text_333,text_334,text_335,text_336,text_337,text_338,text_339,text_340,
text_341,text_342,text_343,text_344,text_345,text_346,text_347,text_348,text_349,text_350,
text_351,text_352,text_353,text_354,text_355,text_356,text_357,text_358,text_359,text_360,
text_361,text_362,text_363,text_364,text_365,text_366,text_367,text_368,text_369,text_370,
text_371,text_372,text_373,text_374,text_375,text_376,text_377,text_378,text_379,text_380,
text_381,text_382,text_383,text_384,text_385,text_386,text_387,text_388,text_389,text_390,
text_391,text_392,text_393,text_394,text_395,text_396,text_397,text_398,text_399,text_400,
text_401,text_402,text_403,text_404,text_405,text_406,text_407,text_408,text_409,text_410,
text_411,text_412,text_413,text_414,text_415,text_416,text_417,text_418,text_419,text_420,
text_421,text_422,text_423,text_424,text_425,text_426,text_427,text_428,text_429,text_430,
text_431,text_432,text_433,text_434,text_435,text_436,text_437,text_438,text_439,text_440,
text_441,text_442,text_443,text_444,text_445,text_446,text_447,text_448,text_449,text_450,
text_451,text_452,text_453,text_454,text_455,text_456,text_457,text_458,text_459,text_460,
text_461,text_462,text_463,text_464,text_465,text_466,text_467,text_468,text_469,text_470,
text_471,text_472,text_473,text_474,text_475,text_476,text_477,text_478,text_479,text_480,
text_481,text_482,text_483,text_484,text_485,text_486,text_487,text_488,text_489,text_490,
text_491,text_492,text_493,text_494,text_495,text_496,text_497,text_498,text_499,text_500,
text_501,text_502,text_503,text_504,text_505,text_506,text_507,text_508,text_509,text_510,
text_511,text_512,text_513,text_514,text_515,text_516,text_517,text_518,text_519,text_520,
text_521,text_522,text_523,text_524,text_525,text_526,text_527,text_528,text_529,text_530,
text_531,text_532,text_533,text_534,text_535,text_536,text_537,text_538,text_539,text_540,
text_541,text_542,text_543,text_544,text_545,text_546,text_547,text_548,text_549,text_550,
text_551,text_552,text_553,text_554,text_555,text_556,text_557,text_558,text_559,text_560,
text_561,text_562,text_563,text_564,text_565,text_566,text_567,text_568,text_569,text_570,
text_571,text_572,text_573,text_574,text_575,text_576,text_577,text_578,text_579,text_580,
text_581,text_582,text_583,text_584,text_585,text_586,text_587,text_588,text_589,text_590,
text_591,text_592,text_593,text_594,text_595,text_596,text_597,text_598,text_599,text_600,
text_601,text_602,text_603,text_604,text_605,text_606,text_607,text_608,text_609,text_610,
text_611,text_612,text_613,text_614,text_615,text_616,text_617,text_618,text_619,text_620,
text_621,text_622,text_623,text_624,text_625,text_626,text_627,text_628,text_629,text_630,
text_631,text_632,text_633,text_634,text_635,text_636,text_637,text_638,text_639,text_640,
text_641,text_642,text_643,text_644,text_645,text_646,text_647,text_648,text_649,text_650,
text_651,text_652,text_653,text_654,text_655,text_656,text_657,text_658,text_659,text_660,
text_661,text_662,text_663,text_664,text_665,text_666,text_667,text_668,text_669,text_670,
text_671,text_672,text_673,text_674,text_675,text_676,text_677,text_678,text_679,text_680,
text_681,text_682,text_683,text_684,text_685,text_686,text_687,text_688,text_689,text_690,
text_691,text_692,text_693,text_694,text_695,text_696,text_697,text_698,text_699,text_700,
text_701,text_702,text_703,text_704,text_705,text_706,text_707,text_708,text_709,text_710,
text_711,text_712,text_713,text_714,text_715,text_716,text_717,text_718,text_719,text_720,
text_721,text_722,text_723,text_724,text_725,text_726,text_727,text_728,text_729,text_730,
text_731,text_732,text_733,text_734,text_735,text_736,text_737,text_738,text_739,text_740,
text_741,text_742,text_743,text_744,text_745,text_746,text_747,text_748,text_749,text_750,
text_751,text_752,text_753,text_754,text_755,text_756,text_757,text_758,text_759,text_760,
text_761,text_762,text_763,text_764,text_765,text_766,text_767,text_768,text_769,text_770,
text_771,text_772,text_773,text_774,text_775,text_776,text_777,text_778,text_779,text_780,
text_781,text_782,text_783,text_784,text_785,text_786,text_787,text_788,text_789,text_790,
text_791,text_792,text_793,text_794,text_795,text_796,text_797,text_798,text_799,text_800,
text_801,text_802,text_803,text_804,text_805,text_806,text_807,text_808,text_809,text_810,
text_811,text_812,text_813,text_814,text_815,text_816,text_817,text_818,text_819,text_820,
text_821,text_822,text_823,text_824,text_825,text_826,text_827,text_828,text_829,text_830,
text_831,text_832,text_833,text_834,text_835,text_836,text_837,text_838,text_839,text_840,
text_841,text_842,text_843,text_844,text_845,text_846,text_847,text_848,text_849,text_850,
text_851,text_852,text_853,text_854,text_855,text_856,text_857,text_858,text_859,text_860,
text_861,text_862,text_863,text_864,text_865,text_866,text_867,text_868,text_869,text_870,
text_871,text_872,text_873,text_874,text_875,text_876,text_877,text_878,text_879,text_880,
text_881,text_882,text_883,text_884,text_885,text_886,text_887,text_888,text_889,text_890,
text_891,text_892,text_893,text_894,text_895,text_896,text_897,text_898,text_899,text_900,
text_901,text_902,text_903,text_904,text_905,text_906,text_907,text_908,text_909,text_910,
text_911,text_912,text_913,text_914,text_915,text_916,text_917,text_918,text_919,text_920,
text_921,text_922,text_923,text_924,text_925,text_926,text_927,text_928,text_929,text_930,
text_931,text_932,text_933,text_934,text_935,text_936,text_937,text_938,text_939,text_940,
text_941,text_942,text_943,text_944,text_945,text_946,text_947,text_948,text_949,text_950,
text_951,text_952,text_953,text_954,text_955,text_956,text_957,text_958,text_959,text_960,
text_961,text_962,text_963,text_964,text_965,text_966,text_967,text_968,text_969,text_970,
text_971,text_972,text_973,text_974,text_975,text_976,text_977,text_978,text_979,text_980,
text_981,text_982,text_983,text_984,text_985,text_986,text_987,text_988,text_989,text_990,
text_991,text_992,text_993,text_994,text_995,text_996,text_997,text_998,text_999,text_1000,
text_1001,text_1002,text_1003,text_1004,text_1005,text_1006,text_1007,text_1008,text_1009,text_1010,
text_1011,text_1012,text_1013,text_1014,text_1015,text_1016,text_1017,text_1018,text_1019,text_1020,
text_1021,text_1022,text_1023,text_1024,text_1025,text_1026,text_1027,text_1028,text_1029,text_1030,
text_1031,text_1032,text_1033,text_1034,text_1035,text_1036,text_1037,text_1038,text_1039,text_1040,
text_1041,text_1042,text_1043,text_1044,text_1045,text_1046,text_1047,text_1048,text_1049,text_1050,
text_1051,text_1052,text_1053,text_1054,text_1055,text_1056,text_1057
};

static const int PROGMEM data[] = {
0  ,20,11,13,15,19, //Start Area
21 ,12,-1,-1,-1,-1, //Area Option 1  
34 ,16,-1,-1,-1,-1, //Area Option 2
51 ,20,-1,-1,-1,-1, //Area Option 3
72 ,7 ,-1,-1,-1,-1, //Area Option 4
80 ,19,13,15,18,-1, //areaLitWoodText
100,14,10,12,-1,-1, //areaLitWoodText_noMouse
115,9 ,-1,-1,-1,-1, //areaLitWoodOpt3
125,7 ,-1,-1,-1,-1, //areaLitWoodOpt3mouse
133,22,15,18,20,-1, //areaCave
156,21,15,17,19,-1, //areaCave_frisbee
178,13,-1,-1,-1,-1, //areaCaveOpt1
192,12,-1,-1,-1,-1, //areaCaveOpt1_frisbee
205, 5,-1,-1,-1,-1, //areaCaveOpt1_wave
211,12,-1,-1,-1,-1, //areaCaveOpt2
224,20,14,17,19,-1, //areaCar
245,16,10,13,15,-1, //areaInsideCar
262,20,-1,-1,-1,-1, //areaInsideCarOpt2
283, 7, 3, 6,-1,-1, //areaCarParts
291, 4,-1,-1,-1,-1, //areaCarParts_comp
296, 8,-1,-1,-1,-1, //areaCarPartsPockets
305,16,13,15,-1,-1, //areaInsideCompleteCar
322,16,-1,-1,-1,-1, //areaInsideCompleteCarOpt1
339,18,-1,-1,-1,-1,  //areaInsideCompleteCarOpt1_CD
358,17,10,12,14,16, //areaCottage
376, 6,-1,-1,-1,-1, //areaCottageOpt2
383,21,14,17,20,-1, //areaInsideCottage
405,20,14,16,19,-1, //areaInsideCottage_keys
426,20,14,16,19,-1, //areaInsideCottage_cd
447,15,-1,-1,-1,-1, //areaInsideCottageOpt1
463,17,-1,-1,-1,-1, //areaInsideCottageOpt1_mouse
481, 7,-1,-1,-1,-1, //areaInsideCottageOpt1_stroke
489,15,-1,-1,-1,-1, //areaInsideCottageOpt2
505,19,-1,-1,-1,-1, //areaInsideCottageOpt2_takeCD
525,17,-1,-1,-1,-1, //areaInsideCottageOpt2_play
543,21,12,15,18,20, //areaGarden
565,22,-1,-1,-1,-1, //areaGardenOpt4
588,21,11,14,17,20, //areaShed
610,18,10,13,16,-1, //areaShed_frisbee
629,12,-1,-1,-1,-1, //areaShedOpt1
642,10,-1,-1,-1,-1, //areaShedOpt1_can
653,13,-1,-1,-1,-1, //areaShedOpt1_got
667,11,-1,-1,-1,-1, //areaShedOpt2
679, 9,-1,-1,-1,-1, //areaShedOpt4
689,19,11,14,16,18, //areaWell
709,18,11,13,15,17, //areaWell_mirror
728, 6,-1,-1,-1,-1, //areaWellOpt1
735,17,-1,-1,-1,-1, //areaWellOpt1_rope
753,18,-1,-1,-1,-1, //areaWellOpt1_hook
772,10,-1,-1,-1,-1, //areaWellOpt1_coin
783,20,14,16,18,-1, //areaOuthouse
804,18,13,15,17,-1, //areaOuthouse_hook
823,11,-1,-1,-1,-1, //areaOuthouseOpt3
835,22,-1,-1,-1,-1, //areaOuthouseOpt3_hook
858, 5,-1,-1,-1,-1, //areaOuthouseOpt3_wee
864,20,14,16,19,-1, //areaBeach
885,19,13,15,18,-1, //areaBeach_snail
905,19,-1,-1,-1,-1, //areaBeachOpt3
925,12,-1,-1,-1,-1, //areaBeachOpt3_search
938,19,10,13,16,18, //areaBoat
958,16,-1,-1,-1,-1, //areaBoatOpt1
975, 9,-1,-1,-1,-1, //areaBoatOpt2
985, 7,-1,-1,-1,-1, //areaBoatOpt2_can
993, 5,-1,-1,-1,-1, //areaBoatOpt2_dneed
999,10,-1,-1,-1,-1, //areaBoatOpt3
1010,6,-1,-1,-1,-1, //areaBoatOpt3_dneed
1017,2,-1,-1,-1,-1, //areaFinish
1020,9,-1,-1,-1,-1, //areaCredits
1030,9,-1,-1,-1,-1,//areaAmyCredits
1040,17,-1,-1,-1,-1 //areaIntro
};

