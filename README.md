# Solutions: Little Book Of Semaphores
```
Copyright 2019 
© Ramon Romero   @RamonRomeroQro

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
```

## Classical Syncronization Problems
| #  | Name                                        | Status |
|----|---------------------------------------------|--------|
| 01 | Producer-Consumer                           | ✅      |
| 02 | Producer-Consumer: Finite Buffer            | ❌      |
| 03 | Readers-Writers                             | ❌      |
| 04 | Readers-Writers: No Starve                  | ❌      |
| 05 | Readers-Writers: Writer Priority            | ❌      |
| 06 | No Starve Mutex                             | ❌      |
| 07 | Dinining Philosophers: Solution 1           | ✅      |
| 08 | Dinining Philosophers; Solution 2           | ❌      |
| 09 | Dinining Philosophers: Tanenbaum's solution | ❌      |
| 10 | Dinining Philosophers: Starving Tanenbaum   | ❌      |
| 11 | Cigarette Smokers                           | ❌      |
| 12 | Cigarette Smokers: Generalized              | ❌      |

## Less-Classical Problems

| #  | Name                             | Status |
|----|----------------------------------|--------|
| 01 | Dining Savages                   | ✅      |
| 02 | Barbershop                       | ✅      |
| 03 | FIFO Barbershop                  | ❌      |
| 04 | Hilzer's Barbershop              | ❌      |
| 05 | The Santa Claus Problem          | ❌      |
| 06 | Building H2O                     | ❌      |
| 07 | River Crossing                   | ❌      |
| 08 | Roller Coaster Problem           | ❌      |
| 09 | Roller Coaster Problem: Multicar | ❌      |





## Not-So-Classical Problems

| #  | Name                       | Status |
|----|----------------------------|--------|
| 01 | Search-Insert-Delete       | ❌      |
| 02 | Unisex Bathroom            | ❌      |
| 03 | Unisex Bathroom: No Starve | ❌      |
| 04 | Baboon Crossing            | ❌      |
| 05 | Modus Hall                 | ❌      |



## Not remotely classical Problems

| #  | Name                   | Status |
|----|------------------------|--------|
| 01 | Sushi Bar: Solution 1  | ❌      |
| 02 | Sushi Bar: Solution 2  | ❌      |
| 03 | Child Care             | ❌      |
| 04 | Child Care : Extended  | ❌      |
| 05 | Room Party             | ❌      |
| 06 | Senate Bus             | ❌      |
| 07 | Faneuil Hall           | ❌      |
| 08 | Faneuil Hall: Extended | ❌      |
| 09 | Dining Hall            | ❌      |
| 10 | Dining Hall: Extended  | ❌      |


----------

## Barrier Hint
n = the  number  of  threads
count = 0
mutex = Semaphore (1)
barrier = Semaphore (0)

### Implementation
rendezvous
mutex.wait()
    count = count + 1
mutex.signal ()

if  count  == n:
    barrier.signal ()
    
barrier.wait()
barrier.signal ()

critical  point