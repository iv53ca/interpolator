close('all');
clear, clc;

pi = 3.1415926535;
step = 12;

angles = [0 : 2 * pi / step : 2 * pi];

% Пока что длина каждого отрезка равна условно 5
% Цикл для угла (поворот синей прямой)
for i_angle_blue = 1 : 1 : length(angles)
  % Цикл для угла (поворот красной прямой)
    for i_angle_red = 1 : 1 : length(angles)
      line1 = [0, 0, 5, 0];
      line2 = [0, 0, 5, 0];

      % Синяя прямая
      sourceX1 = line1(3);
      sourceY1 = line1(4);
      % rotatedX1 = sourceX1;
      % rotatedY1 = sourceY1;
      rotatedX1 = sourceX1 * cos(angles(i_angle_blue)) - sourceY1 * sin(angles(i_angle_blue));
      rotatedY1 = sourceX1 * sin(angles(i_angle_blue)) + sourceY1 * cos(angles(i_angle_blue));

      % Красная прямая
      sourceX2 = line2(3);
      sourceY2 = line2(4);
      rotatedX2 = sourceX2 * cos(angles(i_angle_red)) - sourceY2 * sin(angles(i_angle_red));
      rotatedY2 = sourceX2 * sin(angles(i_angle_red)) + sourceY2 * cos(angles(i_angle_red));

      printf("[%f, %f, 0, 0, 1]\n[0, 0, %f, %f, 1]\n--------------------\n", rotatedX1, rotatedY1, rotatedX2, rotatedY2);

      % figure();
      % hold on, grid on;
      % plot([0, rotatedX1], [0, rotatedY1], '-b');
      % plot([0, rotatedX2], [0, rotatedY2], '-r');
    endfor
endfor

