#pragma once

/**
 * @file graph.hpp
 * @brief Generic directed graph — cycle detection, topological sort, reachability
 *
 * Replaces NetworkX. Pure C++20, adjacency list representation.
 *
 * @author SDT Theory Compiler — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <optional>

namespace sdt::compiler {

template <typename NodeId = std::string>
class DirectedGraph {
public:
    // ─── Mutation ───

    void add_node(const NodeId& id) {
        if (adj_.find(id) == adj_.end()) {
            adj_[id] = {};
            nodes_.push_back(id);
        }
    }

    void add_edge(const NodeId& from, const NodeId& to) {
        add_node(from);
        add_node(to);
        auto& edges = adj_[from];
        if (std::find(edges.begin(), edges.end(), to) == edges.end()) {
            edges.push_back(to);
        }
    }

    void remove_node(const NodeId& id) {
        adj_.erase(id);
        nodes_.erase(std::remove(nodes_.begin(), nodes_.end(), id), nodes_.end());
        for (auto& [node, edges] : adj_) {
            edges.erase(std::remove(edges.begin(), edges.end(), id), edges.end());
        }
    }

    void remove_edge(const NodeId& from, const NodeId& to) {
        auto it = adj_.find(from);
        if (it != adj_.end()) {
            it->second.erase(std::remove(it->second.begin(), it->second.end(), to),
                             it->second.end());
        }
    }

    // ─── Queries ───

    [[nodiscard]] auto has_node(const NodeId& id) const -> bool {
        return adj_.find(id) != adj_.end();
    }

    [[nodiscard]] auto has_edge(const NodeId& from, const NodeId& to) const -> bool {
        auto it = adj_.find(from);
        if (it == adj_.end()) return false;
        return std::find(it->second.begin(), it->second.end(), to) != it->second.end();
    }

    [[nodiscard]] auto successors(const NodeId& id) const -> std::vector<NodeId> {
        auto it = adj_.find(id);
        if (it == adj_.end()) return {};
        return it->second;
    }

    [[nodiscard]] auto predecessors(const NodeId& id) const -> std::vector<NodeId> {
        std::vector<NodeId> result;
        for (auto& [node, edges] : adj_) {
            if (std::find(edges.begin(), edges.end(), id) != edges.end()) {
                result.push_back(node);
            }
        }
        return result;
    }

    [[nodiscard]] auto node_count() const -> size_t { return nodes_.size(); }
    [[nodiscard]] auto nodes() const -> const std::vector<NodeId>& { return nodes_; }

    // ─── Cycle Detection (DFS) ───

    [[nodiscard]] auto find_cycles() const -> std::vector<std::vector<NodeId>> {
        std::vector<std::vector<NodeId>> cycles;
        std::unordered_set<NodeId> visited;
        std::unordered_set<NodeId> in_stack;
        std::vector<NodeId> path;

        for (auto& node : nodes_) {
            if (visited.find(node) == visited.end()) {
                dfs_cycles(node, visited, in_stack, path, cycles);
            }
        }
        return cycles;
    }

    [[nodiscard]] auto has_cycle() const -> bool {
        return !find_cycles().empty();
    }

    // ─── Topological Sort (Kahn's algorithm) ───

    [[nodiscard]] auto topological_sort() const -> std::optional<std::vector<NodeId>> {
        std::unordered_map<NodeId, int> in_degree;
        for (auto& node : nodes_) in_degree[node] = 0;
        for (auto& [node, edges] : adj_) {
            for (auto& dst : edges) in_degree[dst]++;
        }

        std::queue<NodeId> queue;
        for (auto& [node, deg] : in_degree) {
            if (deg == 0) queue.push(node);
        }

        std::vector<NodeId> result;
        while (!queue.empty()) {
            auto cur = queue.front();
            queue.pop();
            result.push_back(cur);

            auto it = adj_.find(cur);
            if (it != adj_.end()) {
                for (auto& next : it->second) {
                    if (--in_degree[next] == 0) queue.push(next);
                }
            }
        }

        if (result.size() != nodes_.size()) return std::nullopt; // Has cycle
        return result;
    }

    // ─── Reachability ───

    [[nodiscard]] auto can_reach(const NodeId& from, const NodeId& to) const -> bool {
        if (from == to) return true;
        std::unordered_set<NodeId> visited;
        return dfs_reach(from, to, visited);
    }

    // Find all nodes reachable from 'start'
    [[nodiscard]] auto reachable_from(const NodeId& start) const -> std::vector<NodeId> {
        std::vector<NodeId> result;
        std::unordered_set<NodeId> visited;
        dfs_collect(start, visited, result);
        return result;
    }

    // Find all ancestors (nodes that can reach 'target')
    [[nodiscard]] auto ancestors_of(const NodeId& target) const -> std::vector<NodeId> {
        std::vector<NodeId> result;
        for (auto& node : nodes_) {
            if (node != target && can_reach(node, target)) {
                result.push_back(node);
            }
        }
        return result;
    }

    // ─── Roots (no predecessors) ───

    [[nodiscard]] auto roots() const -> std::vector<NodeId> {
        std::unordered_set<NodeId> has_predecessor;
        for (auto& [node, edges] : adj_) {
            for (auto& dst : edges) has_predecessor.insert(dst);
        }
        std::vector<NodeId> result;
        for (auto& node : nodes_) {
            if (has_predecessor.find(node) == has_predecessor.end()) {
                result.push_back(node);
            }
        }
        return result;
    }

    // ─── Leaves (no successors) ───

    [[nodiscard]] auto leaves() const -> std::vector<NodeId> {
        std::vector<NodeId> result;
        for (auto& node : nodes_) {
            auto it = adj_.find(node);
            if (it == adj_.end() || it->second.empty()) {
                result.push_back(node);
            }
        }
        return result;
    }

private:
    std::unordered_map<NodeId, std::vector<NodeId>> adj_;
    std::vector<NodeId>                              nodes_;

    void dfs_cycles(const NodeId& node,
                    std::unordered_set<NodeId>& visited,
                    std::unordered_set<NodeId>& in_stack,
                    std::vector<NodeId>& path,
                    std::vector<std::vector<NodeId>>& cycles) const
    {
        visited.insert(node);
        in_stack.insert(node);
        path.push_back(node);

        auto it = adj_.find(node);
        if (it != adj_.end()) {
            for (auto& next : it->second) {
                if (in_stack.find(next) != in_stack.end()) {
                    std::vector<NodeId> cycle;
                    auto start = std::find(path.begin(), path.end(), next);
                    for (auto ci = start; ci != path.end(); ++ci) cycle.push_back(*ci);
                    cycle.push_back(next);
                    cycles.push_back(cycle);
                } else if (visited.find(next) == visited.end()) {
                    dfs_cycles(next, visited, in_stack, path, cycles);
                }
            }
        }

        path.pop_back();
        in_stack.erase(node);
    }

    auto dfs_reach(const NodeId& cur, const NodeId& target,
                   std::unordered_set<NodeId>& visited) const -> bool
    {
        if (cur == target) return true;
        visited.insert(cur);
        auto it = adj_.find(cur);
        if (it != adj_.end()) {
            for (auto& next : it->second) {
                if (visited.find(next) == visited.end()) {
                    if (dfs_reach(next, target, visited)) return true;
                }
            }
        }
        return false;
    }

    void dfs_collect(const NodeId& cur, std::unordered_set<NodeId>& visited,
                     std::vector<NodeId>& result) const
    {
        visited.insert(cur);
        result.push_back(cur);
        auto it = adj_.find(cur);
        if (it != adj_.end()) {
            for (auto& next : it->second) {
                if (visited.find(next) == visited.end()) {
                    dfs_collect(next, visited, result);
                }
            }
        }
    }
};

} // namespace sdt::compiler
