#pragma once

extern DeathZone SeasideHillDeathZones[];

StartPosition op_startpos = { LevelIDs_MetalHarbor, 0xC000, 0xC000, 0xC000, { 230.0f, 1340.0f, -20.0f }, { 210.0f, 1340.0f, -20.0f  }, { 250.0f, 1340.0f, -20.0f } };
StartPosition op_endpos = { LevelIDs_MetalHarbor, 0xF000, 0xF000, 0xF000, { -1300.0f, 140.0f, -45450.0f }, { 2560.0f, 50.0f, -20900.0f }, { 2560.0f, 50.0f, -20900.0f } };
LevelEndPosition op_2pintro = { LevelIDs_MetalHarbor, 0, 0x8000, 0, { 2450.0f, 80.0f, -26110.0f }, { 1950.0f, 80.0f, -27030.0f } };
LevelEndPosition op_endpos23 = { LevelIDs_MetalHarbor, 0, 0, 0, { 2560.0f, 50.0f, -20900.0f }, { 2560.0f, 50.0f, -20900.0f } };

LoopPoint OP_BoulderPath1[]{
	{ 0, 32768, 15.53062f, { -8199.476f, 2021.8f, -39289.95f } },
	{ 0, 0, 23.9397f, { -8199.476f, 2021.315f, -39305.46f } },
	{ 0, 0, 41.67776f, { -8199.476f, 2006.8f, -39323.86f } },
	{ 0, 0, 73.13712f, { -8199.476f, 1971.8f, -39345.2f } },
	{ 0, 0, 96.83673f, { -8199.476f, 1916.8f - 39392.48f } },
	{ 0, 0, 35.04959f, { -8199.476f, 1915.348f, -39489.3f } },
	{ 0, 0, 37.95344f, { -8199.476f, 1906.913f, -39523.08f } },
	{ 0, 0, 30.62774f, { -8199.476f, 1887.5f, -39555.39f } },
	{ 0, 0, 330.98856f, { -8199.476f, 1865.728f, -39576.17f } },
	{ 0, 0, 58.55507f, { -8199.476f, 1595.951f, -39766.59f } },
	{ 0, 0, 29.95662f, { -8199.476f, 1549.82f, -39801.58f } },
	{ 0, 0, 53.22971f, { -8199.476f, 1532.453f, -39825.66f } },
	{ 0, 0, 750.92366f, { -8199.476f, 1518.346f, -39876.89f } },
	{ 0, 0, 57.88111f, { -8199.476f, 1516.8f, -40627.81f } },
	{ 0, 0, 51.90525f, { -8200.563f, 1510.905f, -40685.28f } },
	{ 0, 0, 72.87629f, { -8200.563f, 1492.098f, -40733.62f } },
	{ 0, 0, 317.75434f, { -8200.563f, 1448.77f, -40791.64f } },
	{ 0, 0, 48.72137f, { -8201.449f, 1256.541f, -41044.24f } },
	{ 0, 0, 37.86143f, { -8200.563f, 1232.633f, -41086.32f } },
	{ 0, 0, 78.87513f, { -8200.563f, 1221.401f, -41122.35f } },
	{ 0, 0, 359.45201f, { -8200.563f, 1216.8f, -41201.04f } },
	{ 0, 0, 199.882f, { -8201.156f, 1217.144f, -41560.17f } },
	{ 0, 0, 157.9894f, { -8207.606f, 1270.323f, -41752.74f } },
	{ 0, 0, 124.57877f, { -8227.733f, 1422.902f, -41788.45f } },
	{ 0, 0, 108.69922f, { -8253.146f, 1540.487f, -41756.08f } },
	{ 0, 0, 133.54588f, { -8273.767f, 1588.292f, -41660.66f } },
	{ 0, 0, 118.69448f, { -8294.039f, 1563.348f, -41531.04f } },
	{ 0, 0, 148.82764f, { -8308.927f, 1467.953f, -41462 } },
	{ 0, 0, 160.12598f, { -8340.424f, 1329.254f, -41505.82f } },
	{ 0, 0, 422.12891f, { -8347.82f, 1316.782f,  -41637.88f } },
	{ 0, 0, 954.40812f, { -8351.738f, 1316.8f,  -42059.99f } },
	{ 0, 0, 530.85069f, { -8350.538f, 1592.425f,  -42973.86f } },
	{ 0, 0, 79.43594f, { -8352.397f, 1653.677f,  -43501.24f } },
	{ 0, 0, 270.69413f, { -8349.778f, 1630.176f,  -43577.02f } },
	{ 0, 0, 55.2253f, { -8350.459f, 1416.162f,  -43742.56f } },
	{ 0, 0, 34.91731f, { -8350.459f, 1407.215f,  -43797.02f } },
	{ 0, 0, 405.49216f, { -8350.459f, 1394.554f,  -43829.34f } },
	{ 0, 0, 36.95101f, { -8350.459f, 1226.746f,  -44198.14f } },
	{ 0, 0, 48.33661f, { -8350.459f, 1219.191f,  -44234.27f } },
	{ 0, 0, 306.13118f, { -8350.794f, 1216.8f,  -44282.5f } },
	{ 0, 0, 48.955f, { -8350.505f, 1216.8f,  -44588.63f } },
	{ 0, 30446, 57.35691f, { -8346.961f, 1216.8f,  -44637.45f } },
	{ 0, 28915, 103.15818f, { -8335.284f, 1216.8f,  -44693.6f } },
	{ 0, 26195, 67.99842f, { -8293.946f, 1216.801f,  -44788.11f } },
	{ 0, 24735, 370.965f, { -8252.265f, 1216.8f,  -44841.83f } },
	{ 0, 0, 165.73481f, { -7988.996f, 1216.8f,  -45103.18f } },
	{ 0, 0, 879.71194f, { -7877.814f, 1183.815f,  -45221.35f } },
	{ 0, 0, 288.11582f, { -7311.499f, 821.0714f,  -45788.4f } },
	{ 0, 0, 0.7998f, { -7105.55f, 816.7998f,  -45989.82f } },
	{ 0, 25281, 125.87486f, { -7030.236f, 816.7998f,  -46067.01f } },
	{ 0, 27694, 101.69069f, { -6958.198f, 816.7998f,  -46170.23f } },
	{ 0, 30606, 108.72652f, { -6919.291f, 816.7998f,  -46264.18f } },
	{ 0, 32768, 420.05081f, { -6903.225f, 816.7998f,  -46371.71f } },
	{ 0, 0, 51.56021f, { -6903.02f, 816.7998f,  -46791.76f } },
	{ 0, 0, 59.9947f, { -6903.02f, 813.8428f,  -46843.18f } },
	{ 0, 0, 56.06542f, { -6903.02f, 796.0553f,  -46900.46f } },
	{ 0, 0, 279.24966f, { -6900.309f, 772.8831f,  -46951.03f } },
	{ 0, 0, 530.36253f, { -6900.309f, 654.744f,  -47203.71f } },
	{ 0, 0, 46.26832f, { -6900.309f, 430.4922f,  -47684.1f } },
	{ 0, 0, 43.06006f, { -6900.309f, 418.0757f,  -47728.65f } },
	{ 0, 0, 188.75169f, { -6900.309f, 416.7999f,  -47771.66f } },
	{ 0, 0, 86.66143f, { -6900.309f, 416.7999f,  -47960.41f } },
	{ 0, 33652, 85.85898f, { -6909.676f, 416.7999f,  -48046.56f } },
	{ 0, 37093, 101.82588f, { -6931.784f, 416.7999f,  -48129.52f } },
	{ 0, 40604, 89.50214f, { -6981.608f, 416.7999f,  -48218.32f } },
	{ 0, 43153, 86.86103f, { -7049.556f, 416.7999f,  -48276.57f } },
	{ 0, 46993, 99.47424f, { -7125.912f, 416.7999f,  -48317.97f } },
	{ 0, 49152, 115.01978f, { -7220.277f, 416.7999f,  -48349.43f } },
	{ 0, 0, 179.56078f, { -7335.294f, 416.7999f,  -48349.43f } },
	{ 0, 0, 32.74251f, { -7514.853f, 416.7999f,  -48349.43f } },
	{ 0, 0, 46.15885f, { -7547.546f, 415.0693f,  -48349.43f } },
	{ 0, 0, 40.78744f, { -7591.816f, 402.1988f,  -48349.43f } },
	{ 0, 0, 367.97942f, { -7628.8f, 385.1343f,  -48349.43f } },
	{ 0, 0, 46.27059f, { -7958.146f, 221.7093f,  -48349.43f } },
	{ 0, 0, 44.06305f, { -8000.009f, 202.82375f,  -48349.43f } },
	{ 0, 0, 43.60546f, { -8042.963f, 193.47788f,  -48349.43f } },
	{ 0, 0, 323.07599f, { -8086.498f, 191.7999f,  -48349.43f } },
	{ 0, 0, 150.20586f, { -8409.573f, 191.7999f,  -48349.43f } },
	{ 0, 0, 147.42115f, { -8553.729f, 234.5499f,  -48349.43f } },
	{ 0, 0, 728.09727f, { -8632.598f, 110.799897f,  -48349.43f } },
	{ 0, 0, 0, { -8690.392f, -615.9501f,  -48349.43f } }
};

LoopPoint OP_BoulderPath2[]{
	{ 0, 24735, 41.10425f, { -8294.756f, 1359.3f,  -44960.75f } },
	{ 0, 0, 60.22448f, { -8264.563f, 1359.47f,  -44988.64f } },
	{ 0, 0, 229.58845f, { -8222.312f, 1342.66f,  -45027.84f } },
	{ 0, 0, 122.68341f, { -8082.976f, 1223.398f,  -45165.6f } },
	{ 0, 0, 66.39821f, { -7982.7f, 1209.992f,  -45234.8f } },
	{ 0, 0, 893.55935f, { -7930.722f, 1185.981f,  -45267.7f } },
	{ 0, 0, 280.20506f, { -7354.46f, 819.9731f,  -45843.63f } },
	{ 0, 0, 102.46183f, { -7158.626f, 816.7998f,  -46044 } },
	{ 0, 25281, 101.42168f, { -7084.526f, 816.7998f,  -46114.76f } },
	{ 0, 27694, 71.31666f, { -7023.802f, 816.7998f,  -46195.99f } },
	{ 0, 30606, 113.37147f, { -6995.326f, 816.7998f,  -46261.37f } },
	{ 0, 32768, 419.61104f, { -6975.046f, 816.7998f,  -46372.91f } },
	{ 0, 0, 50.8023f, { -6974.559f, 816.7997f,  -46792.52f } },
	{ 0, 0, 59.9947f, { -6974.559f, 813.8428f,  -46843.18f } },
	{ 0, 0, 55.99984f, { -6974.559f, 796.0553f,  -46900.46f } },
	{ 0, 0, 279.24966f, { -6974.559f, 772.8831f,  -46951.03f } },
	{ 0, 0, 530.36253f, { -6974.559f, 654.744f,  -47203.71f } },
	{ 0, 0, 46.26832f, { -6974.559f, 430.4922f,  -47684.1f } },
	{ 0, 0, 43.06006f, { -6974.559f, 418.0757f,  -47728.65f } },
	{ 0, 0, 188.75236f, { -6974.559f, 416.7999f,  -47771.66f } },
	{ 0, 0, 92.00282f, { -6974.059f, 416.7999f,  -47960.41f } },
	{ 0, 33652, 79.6689f, { -6980.551f, 416.7999f,  -48052.18f }} ,
	{ 0, 37093, 71.89883f, { -7007.159f, 416.7999f,  -48127.27f } },
	{ 0, 40604, 81.22105f, { -7045.733f, 416.7999f,  -48187.94f } },
	{ 0, 43153, 81.29753f, { -7110.306f, 416.7999f,  -48237.2f } },
	{ 0, 46993, 74.65772f, { -7186.662f, 416.7999f,  -48265.1f } },
	{ 0, 49152, 74.52129f, { -7260.777f, 416.7999f,  -48274.05f } },
	{ 0, 0, 179.56078f, { -7335.294f, 416.7999f,  -48274.05f } },
	{ 0, 0, 32.74251f, { -7514.853f, 416.7999f,  -48274.05f } },
	{ 0, 0, 46.15885f, { -7547.546f, 415.0693f,  -48274.05f } },
	{ 0, 0, 40.78744f, { -7591.816f, 402.1988f,  -48274.05f } },
	{ 0, 0, 367.97942f, { -7628.8f, 385.1343f,  -48274.05f } },
	{ 0, 0, 46.27059f, { -7958.146f, 221.7093f,  -48274.05f } },
	{ 0, 0, 44.06305f, { -8000.009f, 202.82375f,  -48274.05f } },
	{ 0, 0, 43.60546f, { -8042.963f, 193.47788f,  -48274.05f } },
	{ 0, 0, 323.07599f, { -8086.498f, 191.7999f,  -48274.05f } },
	{ 0, 0, 150.20586f, { -8409.573f, 191.7999f,  -48274.05f } },
	{ 0, 0, 147.42115f, { -8553.729f, 234.5499f,  -48274.05f } },
	{ 0, 0, 728.09727f, { -8632.598f, 110.799897f,  -48274.05f } },
	{ 0, 0, 0, { -8690.392f, -615.9501f,  -48274.05f } },
};

LoopPoint OP_BoulderPath3[]{
	{ 0, 32768, 84.37756f, { -6792.602f, 959.2126f,  -46489.87f } },
	{ 0, 0, 170.24334f, { -6800.55f, 942.8667f,  -46572.09f } },
	{ 0, 0, 134.35714f, { -6805.244f, 849.3482f,  -46714.04f } },
	{ 0, 0, 61.04037f, { -6812.559f, 813.8428f,  -46843.18f } },
	{ 0, 0, 55.99984f, { -6823.809f, 796.0553f,  -46900.46f } },
	{ 0, 0, 279.24966, { -6823.809f, 772.8831f,  -46951.03f } },
	{ 0, 0, 530.36253f, { -6823.809f, 654.744f,  -47203.71f } },
	{ 0, 0, 46.26832f, { -6823.809f, 430.4922f,  -47684.1f } },
	{ 0, 0, 43.06006f, { -6823.809f, 418.0757f,  -47728.65f } },
	{ 0, 0, 188.75236f, { -6823.809f, 416.7999f,  -47771.66f } },
	{ 0, 0, 111.69065f, { -6823.309f, 416.7999f,  -47960.41f } },
	{ 0, 33652, 130.22131f, { -6836.551f, 416.7999f,  -48071.31f } },
	{ 0, 37093, 111.82968f, { -6881.159f, 416.7999f,  -48193.65f } },
	{ 0, 44060, 110.53483f, { -6944.483f, 416.7999f,  -48285.82f } },
	{ 0, 43153, 142.66435f, { -7030.431f, 416.7999f,  -48355.32f } },
	{ 0, 46993, 102.46242f, { -7158.537f, 416.7999f,  -48418.1f } },
	{ 0, 49152, 74.52129f, { -7260.777f, 416.7999f,  -48424.8f } },
	{ 0, 0, 179.56078f, { -7335.294f, 416.7999f,  -48424.8f } },
	{ 0, 0, 32.74251f, { -7514.853f, 416.7999f,  -48424.8f } },
	{ 0, 0, 46.15885f, { -7547.546f, 415.0693f,  -48424.8f } },
	{ 0, 0, 40.78744f, { -7591.816f, 402.1988f,  -48424.8f } },
	{ 0, 0, 367.97942f, { -7628.8f, 385.1343f,  -48424.8f } },
	{ 0, 0, 46.27059f, { -7958.146f, 221.7093f,  -48424.8f } },
	{ 0, 0, 44.06305f, { -8000.009f, 202.82375f,  -48424.8f } },
	{ 0, 0, 43.60546f, { -8042.963f, 193.47788f,  -48424.8f } },
	{ 0, 0, 323.07599f, { -8086.498f, 191.7999f,  -48424.8f } },
	{ 0, 0, 150.20586f, { -8409.573f, 191.7999f,  -48424.8f } },
	{ 0, 0, 147.42115f, { -8553.729f, 234.5499f,  -48424.8f } },
	{ 0, 0, 728.09727f, { -8632.598f, 110.799897f,  -48424.8f } },
	{ 0, 0, 0, { -8690.392f, -615.9501f,  -48424.8f } }
};

LoopHead OP_BoulderPaths[]{
	{ 0, 81, 13859.4589f, OP_BoulderPath1, nullptr },
	{ 0, 40, 6461.67217f, OP_BoulderPath2, nullptr },
	{ 0, 30, 4527.60408f, OP_BoulderPath3, nullptr },
};