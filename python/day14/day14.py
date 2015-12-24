from collections import namedtuple

Reindeer = namedtuple('Reindeer', ['speed', 'fly_time', 'rest_time'])


TIME = 2503

rs = [Reindeer(27,  5, 132),
      Reindeer(22,  2,  41),
      Reindeer(11,  5,  48),
      Reindeer(28,  5, 134),
      Reindeer( 4, 16,  55),
      Reindeer(14,  3,  38),
      Reindeer( 3, 21,  40),
      Reindeer(18,  6, 103),
      Reindeer(18,  5,  84)
      ]


def dist(r):
    interval = r.fly_time + r.rest_time
    effective = float(r.speed * r.fly_time) / interval
    d1 = effective * (TIME - (TIME % interval))
    d2 = r.speed * min(TIME % interval, r.fly_time)
    return int(d1 + d2)


if __name__ == "__main__":
    print map(dist, rs);
