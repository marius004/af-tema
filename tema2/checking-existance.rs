#[derive(Debug)]
struct Solution;

#[derive(Debug)]
struct DisjointSet {
    parent: Vec<i32>,
}

impl DisjointSet {
    pub fn new(size: usize) -> Self {
        DisjointSet { parent: vec![-1; size] }
    }

    pub fn find(&mut self, node: usize) -> usize {
        match self.parent[node] {
            root if root < 0 => node,
            root => {
                self.parent[node] = self.find(root as usize) as i32;
                self.parent[node] as usize
            }
        }
    }

    pub fn union(&mut self, lhs: usize, rhs: usize) {
        let mut lhs_root = self.find(lhs);
        let mut rhs_root = self.find(rhs);

        if lhs_root == rhs_root {
            return;
        }

        if -self.parent[lhs_root] < -self.parent[rhs_root] {
            std::mem::swap(&mut lhs_root, &mut rhs_root);
        }

        self.parent[lhs_root] += self.parent[rhs_root];
        self.parent[rhs_root] = lhs_root as i32;
    }
}

impl Solution {
    pub fn distance_limited_paths_exist(n: i32, edges: Vec<Vec<i32>>, queries: Vec<Vec<i32>>) -> Vec<bool> {
        let mut queries = 
            queries
            .into_iter()
            .enumerate()
            .map(|(i, q)| (q[2], q[0], q[1], i))
            .collect::<Vec<(i32, i32, i32, usize)>>();

        let mut edges = 
            edges
            .into_iter()
            .map(|e| (e[2], e[0], e[1]))
            .collect::<Vec<(i32, i32, i32)>>();
    
        queries.sort();
        edges.sort();

        let mut dsu = DisjointSet::new(n as usize);
        let mut answer = vec![false; queries.len()];
        
        let mut curr = 0;
        for (w, u, v, i) in queries {
            while curr < edges.len() && edges[curr].0 < w {
                let (_, u, v) = edges[curr];
                dsu.union(u as usize, v as usize);
                curr += 1;
            }

            answer[i] = dsu.find(u as usize) == dsu.find(v as usize);
        }

        answer
    }
}

fn main() {
    let n = 5;
    let edges = vec![vec![0, 1, 10], vec![1, 2, 5], vec![2, 3, 9], vec![3, 4, 13]];
    let queries = vec![vec![0, 4, 14], vec![1, 4, 13]];

    let result = Solution::distance_limited_paths_exist(n, edges, queries);

    println!("{:?}", result);
}